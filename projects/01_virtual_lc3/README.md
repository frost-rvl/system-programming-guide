# Virtual LC3

My LC3 virtual machine, written while following [Write your own virtual machine](https://www.jmeiners.com/lc3-vm).

## Test images

The `objects/` folder has two `.obj` images you can use to test the emulator:

- `2048.obj`: the game 2048, from [rpendleton](https://github.com/rpendleton/lc3-2048)
- `rogue.obj`: a small roguelike tunnel generator, from [justinmeiners](https://github.com/justinmeiners/lc3-rogue)

I did not make them. They are assembled from the original projects.

You can also make your own: write your program in assembly with [WebLC3](https://lc3.cs.umanitoba.ca/), then assemble it with [lc3-asm-to-obj](https://github.com/Somali28/lc3-asm-to-obj).

## License

My code is under the [MIT License](../../LICENSE).

The `.obj` files come from other projects and keep their own licenses (also MIT). See [objects/LICENSES.md](./objects/LICENSES.md).
