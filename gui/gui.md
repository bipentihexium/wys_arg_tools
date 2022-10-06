# WYS ARG GUI

(makes another ultimate abbrevation - WAG, as RWA (RIP WYS ARG))

- [WYS ARG GUI](#wys-arg-gui)
	- [About the GUI](#about-the-gui)
	- [Usage](#usage)
		- [wys_lib.c autocompilation](#wys_libc-autocompilation)
		- [Orientation in the GUI](#orientation-in-the-gui)
		- [Action buttons](#action-buttons)

## About the GUI

It's a GUI which offers all functions of `wys_lib`. I made it to make the decrypt/encrypt functions (+ other stuff from `wys_lib`) are more accessible (and in hope that people will stop using the doc script).

## Usage

Just run the `main.py` with python (3.6+ I think) from the directory it is in.

### wys_lib.c autocompilation

When it detects `gcc` or `clang` and no compiled version of `wys_lib.c` is found, it prompts you to compile it, so you can use the faster alternatives to some functions.

### Orientation in the GUI

![guide image](/gui/doc_images/orientation.png "guide image")

Double-clicking on the things in the tree will load them into the apprpriate spots.

### Action buttons

button title | effect
--- | ---
run | runs the code
decrypt with L1 algorithm | decrypts `data` with `key` (number) using `DB`
dencrypt with L1 algorithm | encrypts `data` with `key` (number) using `DB`
decrypt with L2 algorithm | decrypts `data` with `key`
encrypt with L2 algorithm | encrypts `data` with `key`
decrypt with L5 algorithm | decrypts `data` with `key` (numbers separated by commas)
encrypt with L5 algorithm | encrypts `data` with `key` (numbers separated by commas)
find keys for L2 algorithm | finds keys for specific output (`key`) at the start
character frequency | shows character frequency of `data`
categorized character frequency | shows categorized character frequency of `data`
character mask | replaces all characters not in `key` with dots
minimal chars removed before | deprecated since L5 hints :) (lazy to document)
