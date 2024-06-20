#include "utils.hpp"
#include <openssl/aes.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <json/json.h>
#include <cpprest/http_listener.h>


const std::string Utils::workDir = "workdir";
const std::string Utils::taxiPath = "unicaltaxi-driver";
const std::string Utils::bitoPath = "";

const int Events::TASK_CONFIRMED = 2;
    
const int TASK_TYPE::BUILD = 1;
const int TASK_TYPE::SEND = 2;

const int TASK_STATUS::CREATED = 1;
const int TASK_STATUS::NEW = 2;
const int TASK_STATUS::CONFIRMED = 3;
const int TASK_STATUS::IN_PROGRESS = 4;
const int TASK_STATUS::COMPLETED = 5;
const int TASK_STATUS::FAILED = 6;
const int TASK_STATUS::CANCELED = 7;

std::vector<std::string> split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

std::string base64_encode(const std::string &in)
{
    std::string out;

    std::string base64_encode_b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; //=

    int val = 0, valb = -6;
    for (unsigned char c : in)
    {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0)
        {
            out.push_back(base64_encode_b[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6)
        out.push_back(base64_encode_b[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4)
        out.push_back('=');
    return out;
}

RSA *createPrivateRSA(std::string key)
{
    RSA *rsa = NULL;
    const char *c_string = key.c_str();
    BIO *keybio = BIO_new_mem_buf((void *)c_string, -1);
    if (keybio == NULL)
    {
        return 0;
    }
    rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
    return rsa;
}

bool RSASign(RSA *rsa,
             const unsigned char *Msg,
             size_t MsgLen,
             unsigned char **EncMsg,
             size_t *MsgLenEnc)
{
    EVP_MD_CTX *m_RSASignCtx = EVP_MD_CTX_create();
    EVP_PKEY *priKey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(priKey, rsa);
    if (EVP_DigestSignInit(m_RSASignCtx, NULL, EVP_sha256(), NULL, priKey) <= 0)
    {
        return false;
    }
    if (EVP_DigestSignUpdate(m_RSASignCtx, Msg, MsgLen) <= 0)
    {
        return false;
    }
    if (EVP_DigestSignFinal(m_RSASignCtx, NULL, MsgLenEnc) <= 0)
    {
        return false;
    }
    *EncMsg = (unsigned char *)malloc(*MsgLenEnc);
    if (EVP_DigestSignFinal(m_RSASignCtx, *EncMsg, MsgLenEnc) <= 0)
    {
        return false;
    }
    EVP_MD_CTX_destroy(m_RSASignCtx);
    return true;
}

std::string signMessage(std::string privateKey, std::string plainText)
{
    RSA *privateRSA = createPrivateRSA(privateKey);
    unsigned char *encMessage;
    size_t encMessageLength;
    RSASign(privateRSA, (unsigned char *)plainText.c_str(), plainText.length(), &encMessage, &encMessageLength);
    std::string str1((char *)(encMessage), encMessageLength);
    free(encMessage);
    return base64_encode(str1);
}

std::string url_encode(const std::string &value)
{
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (std::string::const_iterator i = value.begin(), n = value.end(); i != n; ++i)
    {
        std::string::value_type c = (*i);

        // Keep alphanumeric and other accepted characters intact
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
        {
            escaped << c;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << std::uppercase;
        escaped << '%' << std::setw(2) << int((unsigned char)c);
        escaped << std::nouppercase;
    }

    return escaped.str();
}

void generateOAuth2Token()
{
    Json::Value jwt_header;
    Json::Value jwt_claim_set;
    std::time_t t = std::time(NULL);
    Json::FastWriter fastWriter;

    /* Create jwt header */
    jwt_header["alg"] = "RS256";
    jwt_header["typ"] = "JWT";

    /* Create jwt claim set */
    jwt_claim_set["iss"] = "raava-musicplayer@raava-musicplayer.iam.gserviceaccount.com";
    jwt_claim_set["scope"] = "https://www.googleapis.com/auth/androidpublisher";
    jwt_claim_set["aud"] = "https://oauth2.googleapis.com/token";
    jwt_claim_set["iat"] = std::to_string(t);        /* issued time */
    jwt_claim_set["exp"] = std::to_string(t + 3600); /* expire time*/

    // web token
    std::stringstream jwt_ss;

    // header
    jwt_ss << base64_encode(fastWriter.write(jwt_header));
    jwt_ss << ".";

    // claim set
    jwt_ss << base64_encode(fastWriter.write(jwt_claim_set));

    // signature
    std::string signed_msg = signMessage(
        "-----BEGIN PRIVATE KEY-----\nMIIEvAIBADANBgkqhkiG9w0BAQEFAASCBKYwggSiAgEAAoIBAQCmX/nK4OOU83jB\nTelmSAQDigYIoWggIN37KTCWUHlIa//mmKyDso1wiKzDphcWknokA24UBuGIPDnO\nPd+E+xOVgo9k1choOC8+s+kqnjorYet+pJ3tmFX7uoWdY/lcUIBYypiUkc4mGeYh\n8W5YLbtwINLFAIR6HE72i83ZDN4vaO6TvebDc/ZMy10uRSsBPKi9nhjpfTrCQJUl\nKpp066RQ9spwAS7+xhcYOEbrvSFxBv1VOFNvV0/8dy+FXBQM7hZbst32tt7L0o/S\nWukXcPx+fUVBQhIBYClbUEL3o+IgCVr4V6h4x68LpUI9kCS8e52xZgIl7DMgppOb\na/WVahsNAgMBAAECggEAFyIkMOXpLwZVhYdISzz7NeTEpwGOYV1AkFIvW88vtfay\nW8Vhw2QZz4ppf0DCWBSg4A4MCcPVKyS4oukugaaJmBHRz2L8XSVmyFCqvI7IpsyU\nOoU4Ile6qOhL+ND0VLYqym3NHmdRozGZsqGHxsIBHHur4tGKGhKCljxlMGdeI3g5\nfREGTtI6Zm9Ai4jA3mIuSvrDZN0oRdGmV4i8w28cDvT5w33QLJEnt5S58h+x4bWz\n0oXVxcBH0jJsVeUi8LGVpU0Vb42Uj3BAknweJ16YN96AXI73G8pzs0pL6J+Jo7WV\nd3sow9FGAua0kdkwY3ZvxcrIYUsXmSMvZc+n450QTwKBgQDjozJqjD6+BsYsA1+M\nTUmXZV+K9M20zaBpkprtNMDrJ5DuHA9i8HWosMpsy1/jHJZWRBT7DB3q21yoFy6o\nlSM4idjSQZ8QNetaTDNGkgZniW4t6sUJwXGac8ezvVOM9UNwkopQ3AYk3ZdCSsqD\najeL90GV3ZJKqBelzC5maDJtAwKBgQC7Grn/Rm71luy1l1tRx5luYphbtRhV3+Ue\n4hrpqRIdITjHXwoJdQcriQ7wK3iextj54S2s4C5+KTrSQw4WHH0UqTjwLBFM2ate\nvohewrHhUNj6HoDcvXcJHhAFCgl5W7vBRGx71toR6/WLoGjGdNbvLhTpIIQF4M30\nibjefY0yrwKBgHbgtiaAYQ+51+oKRO6vOfxPW2rk1zxRmjEn97Jit1DW09AVZU+l\nBbz3vm68crHXLweT/GTyefk5X5UErkApyj/vdQSwclHz5pm8a5ayEZgmZBykmwuy\nMxKW3jaWa7iUKQjz7jm1/ZtpAWIETuf8I0/76wtJr+k/CUJzc9PVHGhjAoGACESW\nE4G5RYD11NBraKG5VfdlZCgMez75kPPM3KZr9n2RVL4OY3yYZIQZ9OL24Y1H6ULa\nEdmWNFz+DGyKIs//dvpDWdmYqhy0ReuFeyp/UcWQ0PyoFRkKOYzqiE55PLOhCFlN\nses8l64lm5XrC1n+ZXNT2TlmnBvi/ftX//zsUGECgYAtJgfb7DqKkIt0G7ifaxRb\nTE00iRuZYCmhpafRWRQy9fId0Qub2mLPee/298k3oPvJgpKosOcBTRLuKFbiY5Vm\nkSWOcmbZ4O85HEB+AdcTWVc3IyyV5VwuwruhIzI8Qb1Lv0eqnWr9Bai8FgZRcSZg\nJQAjE0nUHI2HssfVM1OFIA==\n-----END PRIVATE KEY-----\n",
        jwt_ss.str());

    jwt_ss << "." << signed_msg;

    std::stringstream post_body_ss;
    post_body_ss << "curl -d '";
    post_body_ss << "grant_type=" << url_encode("urn:ietf:params:oauth:grant-type:jwt-bearer");
    post_body_ss << "&assertion=" << url_encode(jwt_ss.str());
    post_body_ss << "' https://oauth2.googleapis.com/token";
    std::string post_body = post_body_ss.str();
    std::cout << post_body << std::endl;
}