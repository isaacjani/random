# Random projects that I am working on
These are my projects that are in very early development.

## C Web Summarizer

A simple command-line web summarizer written in 88 lines of C.

The program downloads a websites HTML using libcurl, parses the HTML using libxml2, extracts paragraph (`<p>`) text, and creates a basic summary by selecting sentences from the the extracted text.

## Features

- Downloads html from a URL
- Parses HTML with libxml2
- Extracts text from `<p>` elements
- Allows you to choose the number of sentences
- Filters out very short sentences
- Automatically deletes the downloaded `page.html` file when finished
- Runs entirely from the terminal

## Requirements

You need:

- GCC
- libcurl
- libxml2



## Packages for this repository

### Ubuntu / Debian

```bash
sudo apt install gcc libcurl4-openssl-dev libxml2-dev
```
### Fedora

```bash
sudo dnf install gcc libcurl-devel libxml2-devel
```

### Arch Linux

```bash
sudo pacman -S gcc curl libxml2
```

### MacOS
```bash
brew install gcc curl libxml2
```

### Windows MSYS2

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-ucrt-x86_64-curl
pacman -S mingw-w64-ucrt-x86_64-libxml2

