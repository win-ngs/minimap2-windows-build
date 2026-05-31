# minimap2 for Windows: Unofficial Community Build

This repository provides an unofficial Windows build of
[minimap2](https://github.com/lh3/minimap2) 2.31-r1302.

minimap2 is a command-line sequence alignment tool. The upstream project is
primarily built for Unix-like environments. This repository vendors the
minimap2 2.31-r1302 source tree and applies a small MSYS2-UCRT64 compatibility
patch so that `minimap2.exe` can be built and used as a native Windows program.

These builds are not produced, endorsed, or supported by the upstream minimap2
project. For minimap2 itself, see the upstream repository:

https://github.com/lh3/minimap2

## Downloading minimap2 for Windows

Prebuilt Windows binaries are available from the
[Releases](https://github.com/win-ngs/minimap2-windows-build/releases) page
of this repository.

Download the latest release archive, for example:

```text
minimap2-2.31-r1302-windows-x86_64-ucrt64.zip
```

After extracting the archive, you should see:

```text
minimap2-2.31-r1302-windows-x86_64-ucrt64/
  minimap2.exe
  libwinpthread-1.dll
  zlib1.dll
```

Keep the DLL files in the same folder as `minimap2.exe`.

## How to Use

This Windows build uses the same command-line options as upstream minimap2. For
detailed usage and options, refer to the upstream
[minimap2 documentation](https://github.com/lh3/minimap2).

1. Download the ZIP file.
2. Extract the ZIP file.
3. Open PowerShell.
4. Move into the extracted folder.
5. Run `minimap2.exe`.

Example:

```powershell
cd C:\Users\you\Downloads\minimap2-2.31-r1302-windows-x86_64-ucrt64
.\minimap2.exe --version
.\minimap2.exe -h
```

Example long-read mapping run:

```powershell
.\minimap2.exe -ax map-ont .\reference.fa .\reads.fastq.gz -o .\aln.sam
```

Example short-read paired-end run:

```powershell
.\minimap2.exe -ax sr .\reference.fa .\reads_R1.fastq.gz .\reads_R2.fastq.gz -o .\aln.sam
```

Keep the extracted files together. Do not move only `minimap2.exe` to another
folder, because the `.dll` files in the ZIP are needed for the program to start.

## Source Tree

The patched source tree is included in this repository:

```text
minimap2-2.31-patch/
```

The upstream minimap2 README and license are kept inside that directory:

```text
minimap2-2.31-patch/README.md
minimap2-2.31-patch/LICENSE.txt
```

Build outputs such as `minimap2.exe`, `sdust.exe`, `minimap2-lite.exe`, object
files, and static libraries are not meant to be committed to git. Release ZIP
files should be published through GitHub Releases.

## Runtime DLLs included in the release archive

The release archive includes the following MSYS2 UCRT64 runtime DLLs:

```text
libwinpthread-1.dll
zlib1.dll
```

These DLLs are required to run this MSYS2 UCRT64 build of `minimap2.exe`
outside the MSYS2 environment.

The DLLs are redistributed unmodified from MSYS2 packages.

License information for these bundled DLLs is provided in
[THIRD_PARTY_NOTICES.txt](THIRD_PARTY_NOTICES.txt) in this repository.

## Building from Source

You do not need to build minimap2 yourself if you only want to use the released
Windows binary. This section is for maintainers or users who want to recreate
the build.

Install [MSYS2](https://www.msys2.org/) first. Open the MSYS2-UCRT64 shell and
install the build tools and zlib development package:

```sh
pacman -S --needed \
  base-devel \
  mingw-w64-ucrt-x86_64-gcc \
  mingw-w64-ucrt-x86_64-zlib
```

Build minimap2:

```sh
cd /c/path/to/minimap2-windows-build/minimap2-2.31-patch
make
```

The executable is created as:

```text
minimap2-2.31-patch/minimap2.exe
```

## Validation Performed

This patched build was checked with MSYS2-UCRT64 using:

```text
gcc 16.1.0
zlib 1.3.1
```

The following checks were run:

```text
make
make extra
gzip-compressed FASTA through stdin -> minimap2 mapping
redirected SAM output checked for LF-only line endings
redirected help output checked for LF-only line endings
.mmi index dump/load with Windows C:\ paths
gzip-compressed FASTA through stdin -> sdust
git diff --check
```

The gzip-through-stdin validation confirms that UCRT64 text-mode file descriptor
translation does not corrupt compressed input. The redirected-output validation
confirms that SAM/help output written to files or pipes keeps LF line endings.

## MSYS2-UCRT64 Compatibility Patch

The upstream minimap2 2.31-r1302 source compiles in MSYS2-UCRT64, but native
Windows file-descriptor text mode can change bytes on standard streams. That is
risky for gzip-compressed stdin and can also make redirected SAM/PAF output use
CRLF while `-o FILE` output uses LF.

The compatibility patch is limited to Windows/UCRT64 standard stream and binary
open handling:

| File | Change | Reason |
|---|---|---|
| `minimap2-2.31-patch/mmio.h` | Added `mm_gzopen_read()` and `mm_set_stdout_binary_if_redirected()` | Centralizes Windows/UCRT64 binary-mode handling for stdin and redirected stdout |
| `minimap2-2.31-patch/bseq.c`, `index.c`, `sdust.c`, `python/cmappy.h` | Replaced direct `gzdopen(stdin)` / `gzopen()` read paths with `mm_gzopen_read()` | Ensures gzip input from stdin is read after `_setmode(_fileno(stdin), _O_BINARY)`, including library and secondary executable paths |
| `minimap2-2.31-patch/main.c` | Sets stdout to binary only when stdout is not a TTY | Keeps redirected and piped SAM/PAF output LF-only while avoiding staircase display in classic Windows consoles |
| `minimap2-2.31-patch/index.c` | Opens files with `O_BINARY` in `mm_idx_is_idx()` on Windows | Avoids text-mode translation during low-level `.mmi` magic and size checks |
| `minimap2-2.31-patch/setup.py` | Added `mmio.h` to extension build dependencies | Ensures Python extension rebuild tracking includes the compatibility header |

## License

minimap2 is distributed under the MIT License.

See [LICENSE](LICENSE) and
[minimap2-2.31-patch/LICENSE.txt](minimap2-2.31-patch/LICENSE.txt).

The release archive includes MSYS2 UCRT64 runtime DLLs.  
See [THIRD_PARTY_NOTICES.txt](THIRD_PARTY_NOTICES.txt) for third-party package
and license information.
