# Gas Station Socket Server

Introducing a powerful C++ program designed to revolutionize communication between Node.JS and fuel dispensers in gas stations. Working in conjunction with a React and Electron frontend, this program acts as a crucial middleman, enabling seamless communication and control over the fuel dispensing process. With plans to deploy this technology in a real gas station in the upcoming months, this project has been developed with a strong focus on real-world applications and functionality. While the code is still in the early stages of development, it is capable of listening through a socket and parsing through buffers, paving the way for a full-fledged POS Suite for gas stations. As the driving force behind this innovative project, I'm committed to delivering cutting-edge solutions that will streamline operations and enhance customer experiences in the gas station industry.

> and yes, chatGPT wrote that...

## Building
There shouldn't be any problems building this application under a linux/unix environment; just run the `compile.sh` file and it should run.

## Usage

### Buffer Syntax 

```
[0x00, 0x01, 0x14, 0x00, 0x01]

1st byte : 0x00 keeps the server going, 0x11 terminates the server
2nd byte : type of fuel [e85, e87, e89, Diesel]
3rd byte : dollars in hex [20.XX]
4th byte : decimal in hex  [XX.52] 
5th byte : pump number [pump 1, pump 2, ... etc]

```