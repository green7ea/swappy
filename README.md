# Swappy

Swappy is a utility program made to swap out a glibc `/usr` located in
`/glibc/usr` into a musl system and execute a command. This is used to run
programs which don't quite work under musl. This works really well in Void
Linux.

## Compiling

To compile, run the command:

```
make
```

which will produce the `swappy` executable.

For swappy to be useful, it needs to be executed with mount rights. The easiest
way to do this is to run it as root with `setuid`. Swappy drops the privileges
as soon as possible.

```
sudo chown root.root
sudo chmod 755 swappy
sudo chmod +s swappy
```

## Using

To use swappy, simply call it with the program and arguments to run under the
modified `/usr` as arguments:

```
./swappy qutebrowser
```

will launch `qutebrowser` with the `glibc` `/usr` provided that it and its
dependencies are properly installed.
