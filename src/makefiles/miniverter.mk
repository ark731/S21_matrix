brew:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	echo "ps -A | grep iTerm | grep -v grep | awk '{print $1}' | xargs kill -9 $1" > brew.sh
	echo "open /Applications/iTerm.app \n brew install lcov" >> brew.sh
	echo "brew install check \n brew install cppcheck \n rm brew.sh" >> brew.sh
	sh brew.sh && clear

verter:
	rm -rf ~/Library/Containers/com.docker.docker
	mkdir -p ~/goinfre/Docker/Data
	ln -s ~/goinfre/Docker ~/Library/Containers/com.docker.docker
	open /Applications/Docker.app
	cd ../materials/build && sh run.sh && cd ../../