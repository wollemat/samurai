

<p align="center"> <img src="./icon.png" alt="icon" width="100" height="100" /> </p>

# Samurai

Samurai is a simple password generator for the command line. Simple is the magic word, the source is very simple and clean but additionally the generated passwords are human readable, pronouncable and easily typed. No more 30 character password strings of garbled text that only computers can distinguish.

## Getting Started

To get a build of Sorbet up and running on your local machine the following tools are required:

* A working installment of the GCC compiler
* A working installment of CMake
* A working installment of Make


Building is as simple as running the following command in the root of the project:

```
$ cmake . && make
```

## Deployment

Running Samurai is just as easy as building it. Simply run the build executable and receive your generated password.

```
$ samurai
```

By default, Samurai will generate a single password of 10 characters long, not capitalized, without numbers and special characters. The behavior of Samurai can be altered using a variety of flags:

| Flag | Argument | Description                                        |
|------|----------|----------------------------------------------------|
| -x   | int      | Set the number of passwords that are generated     |
| -l   | int      | Set the length of the generated passwords          |
| -c   | none     | Capitalize the generated passwords                 |
| -s   | none     | Add a special character to the generated passwords |
| -n   | none     | Add numbers to the generated passwords             |
| -h   | none     | Show a usage description                           |


Some examples to get you on your way:

```
$ samurai

	gosyxycamo

$ samurai -x 3

	mepahehav
	lovotezeqe
	mysipapyki

$ samurai -l 5

	pyciz

$ samurai -c

	Betevawony

$ samurai -s

	dafoqalip!

$ samurai -n

	tunajyka42

$ samurai -x 6 -l 12 -c -s -n

	Rajotifez^21
	Gybajecog$11
	Qipaqiwit#28
	Zowitucox?43
	Ryvyliman%83
	Kalicywom-20

$ samurai -h

	Samurai: Human Readable Password Generator

	Usage: samurai [-h] [-x <int>] [-l <int>] [-c] [-s] [-n]

	-h:		 Print this help page.
	-x <int>:	 Set the amount of generated passwords.
	-l <int>:	 Set the length of the generated password.
	-c:		 Enable capitalization of the password.
	-s:		 Add a special character to the password.
	-n:		 Add numbers to the password.
```

Good luck!

## Authors

* **Frederik Christian Slothouber** - *Initial work* - [wollemat](https://github.com/wollemat)
