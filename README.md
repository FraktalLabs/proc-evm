# Proc EVM

[![readme style standard](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

Process Ethereum VM bytecode and/or contracts

Stand-alone C++20 executable used to run EVM bytecode and contracts.
Acts only as the execution layer. Allows users to run bytecode scripts,
deploy contracts, and call contracts on provided state & contexts.

## Table of Contents

- [Install](#install)
- [Usage](#usage)
- [Dependencies](#dependencies)
- [Testing](#testing)
- [Media](#media)
- [Maintainer](#maintainer)
- [License](#license)

## Install

```
make all
```

**NOTE:** [Dependencies](#dependencies) must be compiled & linked into compilation aswell.

## Usage

### Commandline

proc-evm comes with various commandline functions, including :

**Run** - runs bytecode as a script on the state ( no contract call )
```
./bin/proc-evm run --snapshotFile ./path/to/snapshot.json --blockContextFile ./path/to/blockcontext.json --txContextFile ./path/to/txcontext.json --contractCode 600260040160005260206000f3
```

**Deploy** - deploys contract on state using init code ( in the standard EVM way )
```
./bin/proc-evm deploy --snapshotFile ./path/to/snapshot.json --blockContextFile ./path/to/blockcontext.json --txContextFile ./path/to/txcontext.json --contractCode 6001600201600a55600D6014600039600D6000F3600260040160005260206000F3
```

**Deploy At** - deploys contract on state using init code to specified address ( useful in genesis setup )
```
./bin/proc-evm deployAt --snapshotFile ./path/to/snapshot.json --blockContextFile ./path/to/blockcontext.json --txContextFile ./path/to/txcontext.json --contractCode 6001600201600a55600D6014600039600D6000F3600260040160005260206000F3 --deployAddress 4200000000000000000000000000000000000000
```

**Call** - call a contract in state w/ provided args ( in the standard EVM way )
```
./bin/proc-evm call --contractAddress 4200000000000000000000000000000000000000 --snapshotFile ./path/to/snapshot.json --blockContextFile ./path/to/blockcontext.json --txContextFile ./path/to/txcontext.json
```

**Note** : Use `-h` flag on each sub-command to see more options

### Library Usage

This repo contains a library setup aswell, to use proc-evm within your code.

Add include path to compilation `-I./path/to/proc-evm/include`.

Import into your code.
```
#include <proc-evm/proc-evm.h>
```

Use `proc-evm` functionality as desired.
This includes `CallContext`, `Stack`, `Memory`, `Opcodes`, commands, and more.

**NOTE:** [Dependencies](#dependencies) must be compiled & linked into compilation aswell.

## Dependencies

- [intx][intx] : 256-bit (32-byte) unsigned integers
- [ethash][ethash] : Ethereum hash functions
- [evm-cpp-utils][evm-cpp-utils] : EVM state & context types + utils

## Testing

This repo contains various tests under `./test/` to make sure things are working.
To run use :

```
make run-test
make deploy-test
make deploy-at-test
make call-test
```

Check the diff in `./test/snapshot.json` to see if things processed properly.

## Media

![EVM Call Chart](https://github.com/FraktalLabs/docs/blob/master/images/proc-evm/call.jpg)

![EVM Deploy Chart](https://github.com/FraktalLabs/docs/blob/master/images/proc-evm/deploy.jpg)

## Maintainer

Brandon Roberts [@b-j-roberts]

## License

[MIT][MIT]


[intx]: https://github.com/chfast/intx
[ethash]: http://github.com/chfast/ethash
[evm-cpp-utils]: https://github.com/FraktalLabs/evm-cpp-utils
[MIT]: LICENSE
[@b-j-roberts]: https://github.com/b-j-roberts
