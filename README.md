## Source Rebuild for Lightwave Consultants 1985 Cavequest v1.1

### Description
Source reconstructed from original .COM and .000 files. Will compile to

exactly match byte for byte of original.

Original SHA-256

QUEST.COM: c2369d72837f7fb1ab4e1f5dc6a0c36d0d4210a349e9909c4e1601b0d0f44a2a

QUEST.000: 75868e02b2ab9f4d3bb8b5b118a285b730214b85a7c278ce5e7c4c649c068c31


### Tools required / used
DOSBox-X  2026.08.02, Visual Studio SDL2 64-bit, use config file in Support.

IBM PC-DOS v2.10, with PAD256.SYS device in Support.

Borland Turbo Pascal 3.00B.

NORMAL.PAS to work around TP3 and system configuration, see Notes below.


### Notes
#### File offset `$2BBB`

The word beginning at `$2BBB` contains the code segment (`CS`) of the running Turbo Pascal compiler.

The original executable contains:

```text
Offset $2BBB: 10 06
```

which is the little-endian word:

```text
$0610
```

Therefore, the original Cavequest compilation occurred while Turbo Pascal was running with:

```text
CS = $0610
```

This value is written by Turbo Pascal into generated programs so that a program executed from within the Turbo environment can return to the IDE when it terminates.

It is therefore dependent on the DOS memory layout rather than on the Pascal source.

---

#### File offset `$2BBD`

The following word contains Turbo Pascal's data segment (`DS`).

The original bytes are:

```text
Offset $2BBD: C3 0F
```

or:

```text
DS = $0FC3
```

For the specific Turbo Pascal 3.00B `TURBO.COM` used for the reconstruction, the compiler establishes:

```text
DS = CS + $09B3
```

Thus:

```text
$0610 + $09B3 = $0FC3
```

which exactly matches the values embedded in the original Cavequest executable.

Like the CS value, this DS value is used by the Turbo runtime when returning control to the Turbo development environment after an executed program terminates.
