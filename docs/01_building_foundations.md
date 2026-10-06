# Building Foundations

Most topics here have two links: **Get Started** and **Docs**.

- Start with **Get Started**. It will teach you the basics step by step.
- Keep **Docs** on the side when you are working on a project. Use it when you need to check details or when you are stuck.

> NOTE: Most tools here are Linux-focused (`strace` works only on Linux, `rr` works mostly on Linux, and `valgrind` has limited support on newer macOS). If you are on Windows or macOS, use a VM or WSL.

This path is divided into four parts:

- [Debugging and Logging (Tools)](#debugging-and-logging)
- [Computer Architecture](#computer-architecture)
- [Version Control (Tools)](#version-control)
- [Operating Systems Fundamentals](#operating-systems-fundamentals)

## Debugging and Logging

### Printf debugging and logging

If you are using a framework, an IDE, or any other software, most of the time there are `logs`.
They tell you what happened and what the level of each message was (info, warning, error...).

The idea of using `printf` to debug **your program** is the same.
But when things scale, we need more proper tools, so let's look at some of them.

### GDB

[ [Get Started](https://www.recurse.com/blog/5-learning-c-with-gdb) |
[Docs](https://sourceware.org/gdb/documentation/) ]

Use `gdb` or `lldb` to debug your C/C++ program step by step.

Don't forget `-g` with `gcc` to enable debugging on your program.

### Valgrind

[ [Get Started](https://valgrind.org/docs/manual/quick-start.html) |
[Docs](https://valgrind.org/docs/manual/manual.html) ]

Use `valgrind` to detect memory leaks when you use `malloc`, and more...

Read the output messages to understand what happened.

### Record Replay

[ [Get Started](https://www.youtube.com/watch?v=l8QuZLAFCjk&t=113s) |
[Docs](https://github.com/rr-debugger/rr/wiki) ]

Have you ever dreamed of time travel?\
Try `reverse-next` with `rr`.

### Strace

[ [Get Started](https://jvns.ca/strace-zine-unfolded.pdf) |
[Docs](https://www.man7.org/linux/man-pages/man1/strace.1.html) ]

Sometimes you may encounter programs without logs, and instead of guessing what's happening...\
Why not look at what is actually running behind the scenes with `strace`?

Don't worry, you will learn more about system calls in the next chapter.

**SUMMARY**:

- Check your `logs`
- Use `gdb` for general-purpose bugs
- Use `valgrind` to detect memory errors
- Use `rr` to debug crashes that are hard to reproduce or irregular
- Use `strace` when you want to spy on what your program is doing

## Computer Architecture

OK, let's talk seriously now. Before going deeper into code, we need to learn how our code works on our computer. So let's dive into some computer architecture lessons.

**LESSON**: [Crash Course Computer Science](https://www.youtube.com/playlist?list=PL8dPuuaLjXtNlUrzyH5r6jN9ulIgZBpdo), videos **5 to 11**.

**PROJECT**: [Write your own virtual machine](https://www.jmeiners.com/lc3-vm)

This project will help you understand how the **LC3** architecture works.

I have put some `.obj` images under `/projects/01_virtual_lc3/objects` that you can use to test your final emulator. See the [project README](../projects/01_virtual_lc3/README.md) for the sources and licenses.

## Version Control

That first project was not that big...
But think about a large team working together on a big project, with different versions and different tags.

[ [Get Started](https://learngitbranching.js.org/) |
[Docs](https://git-scm.com/docs) ]

Use `git` to track the changes of your project, work with a team, and go back to an older version when something breaks.

## Operating Systems Fundamentals

For now, the hardware part of a computer should be understood.\
But to read this guide, you need a piece of software called an `operating system`, such as Linux, macOS, or even Windows. So let's make our own **LITTLE OS**.

**LESSON**: [Crash Course Computer Science](https://www.youtube.com/watch?v=6-tKOHICqrI&list=PL8dPuuaLjXtNlUrzyH5r6jN9ulIgZBpdo), episodes **17 and 18**.

**PROJECT**: [Little OS Book](https://littleosbook.github.io/)

This project is much harder than the LC3 VM. Take your time, and don't be afraid to go back to C and x86 Assembly basics when you are stuck. The book will take more time to swallow, but I promise it's really worth it.

Don't forget to check the `references` inside the book too. They will help you understand the concepts more deeply.\
As your project gets bigger, search for what an `ADT (Abstract Data Type)` is, and use it to organize your code base.

> REMINDER: Don't copy-paste code. Understand, learn, change it, and test new ideas. And this time, use `git` to manage your project development.

[Next: Core System Programming](./02_core_system_programming.md)
