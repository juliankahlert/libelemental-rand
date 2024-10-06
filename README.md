# libelemental-rand

**libelemental-rand** is a collection of random number generators and related functions designed to provide consistent and reliable random number generation across multiple programming languages. Each language implementation follows an extremely similar API, making it easy to switch between languages or port code while maintaining the same functionality and behavior.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Supported Languages](#supported-languages)
- [API](#api)
  - [Initialization](#initialization)
  - [Generating Random Numbers](#generating-random-numbers)
  - [Generating Gaussian Distributed Random Numbers](#generating-gaussian-distributed-random-numbers)
- [Examples](#examples)
  - [C Example](#c-example)
  - [JavaScript Example](#javascript-example)
- [Contributing](#contributing)
- [License](#license)

## Overview

The `libelemental-rand` library provides a straightforward and flexible API for random number generation, including uniform and Gaussian-distributed random numbers. The library includes language-specific implementations for a variety of popular programming languages, enabling cross-language compatibility and easy code integration.

## Features

- **Cross-language support** with consistent APIs
- **Uniform random number generation** using a linear congruential generator (LCG)
- **Gaussian random number generation** using the Box-Muller transform
- **Customizable parameters** for easy control over seed, multiplier, increment, and modulus values

## Installation

To use `libelemental-rand` in your project, download or clone the repository:

```bash
git clone https://github.com/juliankahlert/libelemental-rand.git
```

Then follow the language-specific installation instructions found in each language directory.

## Usage

Each language-specific directory contains the necessary code files and instructions to integrate `libelemental-rand` into your project. Here’s a basic example in C and JavaScript:

### Supported Languages

The following languages are currently supported:

- C
- JavaScript
- More coming soon!

## API

### Initialization

The library provides an initialization function to set up the random number generator.
You can specify parameters such as seed, multiplier (`a`), increment (`c`), and modulus (`m`).
If these parameters are not specified (0) or `cfg` is `NULL` , default values will be used.

```c
int lcg_init(struct lcg *lcg, struct lcg_cfg *cfg);
```

### Generating Random Numbers

After initializing the generator, you can generate random integers and real values in the range `[0, 1)`:

```c
uint32_t lcg_next(struct lcg *lcg);
float lcg_next_real(struct lcg *lcg);
```

### Generating Gaussian Distributed Random Numbers

To generate Gaussian-distributed random numbers, use the following function:

```c
float lcg_next_gaussian(struct lcg *lcg, float mean, float stddev);
```

## Examples

### C Example

Here’s a simple example in C to get started:

```c
#include <stdio.h>
#include "lcg.h"

int main(void) {
    struct lcg my_lcg;
    lcg_init(&my_lcg, &(struct lcg_cfg) {.seed = 1337});

    printf("Random integer: %u\n", lcg_next(&my_lcg));
    printf("Random real: %f\n", lcg_next_real(&my_lcg));
    printf("Random Gaussian: %f\n", lcg_next_gaussian(&my_lcg, 0.0, 1.0));

    return 0;
}
```

### JavaScript Example

For a similar JavaScript example:

```javascript
import { lcg_init, lcg_next, lcg_next_real, lcg_next_gaussian } from "./lcg.js";

const lcg = lcg_init({ seed: 1337 });

console.log("Random integer:", lcg_next(lcg));
console.log("Random real:", lcg_next_real(lcg));
console.log("Random Gaussian:", lcg_next_gaussian(lcg, 0.0, 1.0));
```

## Contributing

Contributions are welcome! If you would like to add new features, fix bugs, or add support for other languages, please open an issue or submit a pull request.

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Make your changes.
4. Submit a pull request.

Please ensure all contributions follow the project's code style and include appropriate tests.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
