# HSMSimulator

## Description
This project presents behaviour of Hierarchical State Machine based on two applications:
  * State Machine - allows to check correctness of HSM library testing the HSM shown below:

<p align="center">
  <img width="560" height="300" src="https://user-images.githubusercontent.com/23028094/51427062-3b746f00-1bf3-11e9-96cd-0d38a89e6cb5.png">
</p>

  * Alexa Simulator - application which simulates behaviour of alexa device. It has been written to present usage of HSM library for embedded     devices. Application consists of two idependent processes which communicate each other via message queues. The first process is a mock     of alexa device. The second process is a mock of user. 
    The HSM uses in this application is shown below:
    
<p align="center">
  <img width="880" height="320" src="https://user-images.githubusercontent.com/23028094/51427135-074d7e00-1bf4-11e9-80d8-b4d00d476069.png">
</p>
    
## Prerequisities
Make sure you have installed all of the following prerequisites on your development machine:
  * cmake - minimum required version 3.0
  * g++ - version compatible with c++14
  * boost library
  
## Usage
In order to run State Machine and Alexa Simulator applications use `build_linux.sh` as follow:
  * `./build_linux.sh` - to show help:
  
<p align="center">
  <img width="580" height="240" src="https://user-images.githubusercontent.com/23028094/51427514-14b93700-1bf9-11e9-957e-2e46b3be8474.png">
</p>

  * `./build_linux.sh HSMExample` - to build State Machine </br>
     After building, go to `target/bin/` directory and run `./state_machine`
  * `./build_linux.sh AlexaSim` - to build Alexa Simulator</br>
     After building, go to `target/bin/` directory and run executable files in appropriate order:</br>
     Firstly: `./alexa_sim`</br>
     Secondly: `./user`
     
## Author
Hubert Buczyński

## License
This project is licensed under the MIT License
