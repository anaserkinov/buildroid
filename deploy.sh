if [[ "$1" == "--buildD" || "$1" == "--all" ]]; then
    yes | docker image prune
    docker build -t anasxonunical/buildroid:v1.0.0 .
fi

if [[ "$1" == "--pushD" || "$1" == "--all" ]]; then
    docker login -u anasxonunical --password-stdin <docker_token
    #    docker tag anasxonunical/buildroid anasxonunical/buildroid:v1.0.0
    docker push anasxonunical/buildroid:v1.0.0
fi

if [[ "$1" == "--setupServer" ]]; then
    scp host/* root@37.27.20.246:buildroid
    ssh root@37.27.20.246 <<EOF
   cd buildroid
   chmod +x tools.sh
   yes | ./tools.sh --setup
EOF
fi

if [[ "$1" == "--restart" || "$1" == "--all" ]]; then
    if [[ "$2" == "--hard" ]]; then
        scp host/* root@37.27.20.246:buildroid
    fi
    ssh root@37.27.20.246 <<EOF
    cd buildroid
    chmod +x tools.sh
   ./tools.sh --restart
EOF
fi
