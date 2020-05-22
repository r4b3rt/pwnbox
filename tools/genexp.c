#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

char str[] = {"#!/usr/bin/env python3\n# -*- coding: utf-8 -*-\n"
              "import argparse\nparser = argparse.ArgumentParser()\nparser.add_argument('i',nargs='?',)\nparser.add_argument('d',nargs='?',)\nparser.add_argument('r',nargs='?',)\n"
              "from pwn import *\n\n#context.update(arch='i386')\nexe = context.binary = ELF('%s')\nhost, port = '127.0.0.1:10003'.split(':')\ngdbscript = '''\nb main\n'''\n\n"
              "args = parser.parse_args()\nif args.i=='i':\n    context.log_level='debug'\ndef local():\n    return process(exe.path)\ndef remote():\n    return connect(host, port)\nstart = remote if args.r else local\n\n"
              "io = start()\nif args.d=='d':\n    context.terminal = ['tmux', 'split', '-h']\n    gdb.attach(io, gdbscript)\n\nio.interactive()\n"};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s PROGRAM_NAME\n", argv[0]);
        exit(-1);
    }
    FILE *fp = NULL;
    fp = fopen("exp.py", "w");
    fprintf(fp, str, argv[1]);
    fclose(fp);
    if (chmod("exp.py", 0755) != 0)
    {
        perror("chmod");
        exit(-2);
    }
    printf("Exploit.py generated successfully.\n");
    exit(0);
}