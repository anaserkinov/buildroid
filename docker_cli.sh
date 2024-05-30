if [[ $1 == "--build" ]]; then
    command="build"
elif [[ $1 == "--push" ]]; then
    command="push"
elif [[ $1 == "--download" ]]; then
    command="download"
elif [[ $1 == "--init" ]]; then
    command="ini"
else
    command="all"
fi

# if [[ "$command" == "init" ]]; then
#   apt-get update && apt-get install -y curl unzip
# elif [[ "$command" == "download" ]]; then

# else
  if [[ "$command" == "build" || "$command" == "all" ]]; then
    docker build -t anasxonunical/buildroid:v1.0.0 .
  fi

  if [[ "$command" == "push" || "$command" == "all" ]]; then
    docker login -u anasxonunical --password-stdin < docker_token
#    docker tag anasxonunical/buildroid anasxonunical/buildroid:v1.0.0
    docker push anasxonunical/buildroid:v1.0.0
  fi

# fi