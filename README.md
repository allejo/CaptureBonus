# CaptureBonus

A BZFlag plugin that awards a bonus to players who capture the flag.

### Requirements

- BZFlag 2.4.3+ (*latest version available on GitHub is recommended*)

### How to Compile

1. Check out the 2.4.x BZFlag source code from GitHub, if you do not already have it on your server. If you are still using SVN, it is recommended you switch to using Git because all future development of BZFlag will use Git.

        git clone -b 2.4 https://github.com/BZFlag-Dev/bzflag.git

2. Go into the newly checked out source code and then the plugins directory.
        
        cd bzflag/plugins

3. Run a git clone of this repository from within the plugins directory. This should have created a new `CaptureBonus` directory within the plugins directory.

        git clone https://github.com/allejo/CaptureBonus.git

4. The latest BZFlag trunk will contain a script called 'addToBuild.sh' and it will allow you to add the plugin to the build system.

        sh addToBuild.sh CaptureBonus

5. Instruct the build system to generate a Makefile and then compile and install the plugin.

        cd ..; ./autogen.sh; ./configure; make; make install;

## BZDB Variables

    _captureBonus

_captureBonus

- Default: *10*

- Description: The number of extra points a player will be awarded on capturing a flag.


### Using Custom BZDB Variables

Because this plugin utilizes custom BZDB variables, using `-set _captureBonus 10` in a configuration file or in an options block will cause an error; instead, `-setforced` must be used to set the value of the custom variable: `-setforced _captureBonus 90`. These variables can be set and changed normally in-game with the `/set` command.
