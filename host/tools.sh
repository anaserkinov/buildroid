if [ $1 == "--setup" ]; then

sudo apt-get update 

sudo apt-get purge docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin docker-ce-rootless-extras

if [ $2 == "--hard" ]; then
sudo rm -rf /var/lib/docker
sudo rm -rf /var/lib/containerd
sudo rm -rf /usr/bin/docker-compose
sudo rm -rf /usr/local/bin/docker-compose
fi

for pkg in docker.io docker-doc docker-compose docker-compose-v2 podman-docker containerd runc; do sudo apt-get remove $pkg; done
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Add the repository to Apt sources:
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

sudo apt-get update

sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose docker-compose-plugin

elif [ $1 == "--restart" ]; then

SESSION_NAME="buildroid"

if screen -list | grep -q "\.${SESSION_NAME}\b"; then
    screen -S "${SESSION_NAME}" -X quit
fi

screen -dmS "${SESSION_NAME}"

COMMANDS=("yes | docker image prune" \
  "cd /root/buildroid" \
  "docker-compose down" \
  "docker-compose pull" \
  "docker-compose up"
)

for cmd in "${COMMANDS[@]}"; do
    screen -S $SESSION_NAME -X stuff "$cmd"$'\n'
done

elif [ $1 == "--debug" ]; then

gdb --args ./build/Buildroid

fi