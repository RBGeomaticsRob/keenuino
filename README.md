# Keenuino
## An IoT project to link an Arduino Yun to Keen.io using the Keen Arduino SDK

### Setup
You will need to install the [keen-arduino](https://github.com/keen/keen-arduino) library, remebering to upload the root certificate to your Yun, instructions are [here](https://github.com/keen/keen-arduino/tree/master/tools)

Create a project at [keen.io](https://keen.io)

Locally create a keys.h to your root directory and include your keen.io project ID and WriteKey. This file is in the .gitignore to avoid pushing your credentials to GitHub.

```c
#define KEENPROJECTID "aaaaa000000"         //replace with your keen.io Project ID
#define KEENWRITEKEY "aaaaaaaaaaaaa0000000"  //replace with your keen.io Project Write Key
```

Upload the sketch to your Arduino YUN.

