# minimap2 for Windows: Unofficial Windows binaries

This repository provides a minimap2 build that runs natively on Windows.
The release archive includes a pre-compiled `minimap2.exe` that users can run
without building from source.

This is **not an official minimap2 release**.  
Official minimap2 repository: https://github.com/lh3/minimap2

This build is based on upstream minimap2 2.31-r1302.

The Windows executable was built from the unmodified upstream source code using
[MSYS2 UCRT64](https://www.msys2.org/docs/environments/).

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

## Running minimap2 from PowerShell

minimap2 is a command-line program. Open PowerShell, then move into the
extracted folder before running it:

```powershell
# Replace this path with the folder where you extracted the ZIP file.
cd C:\Users\your_name\Downloads\minimap2-2.31-r1302-windows-x86_64-ucrt64
```

Check the version:

```powershell
.\minimap2.exe --version
```

Example long-read mapping run:

```powershell
.\minimap2.exe -ax map-ont .\reference.fa .\reads.fastq.gz -o .\aln.sam
```

Example short-read paired-end run:

```powershell
.\minimap2.exe -ax sr .\reference.fa .\reads_R1.fastq.gz .\reads_R2.fastq.gz -o .\aln.sam
```

For detailed usage and options, refer to the
[official minimap2 documentation](https://github.com/lh3/minimap2).

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

## Build from source

This section is for users who want to build `minimap2.exe` themselves.

Install [MSYS2](https://www.msys2.org/), then open the **MSYS2 UCRT64**
terminal from the Windows Start menu.

Update MSYS2:

```bash
pacman -Syu
```

If MSYS2 asks you to close the terminal, close it, reopen **MSYS2 UCRT64**,
and run again:

```bash
pacman -Syu
```

Install the required build tools and zlib development package:

```bash
pacman -S --needed base-devel git mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-zlib
```

Build minimap2 from the upstream source:

```bash
git clone https://github.com/lh3/minimap2
cd minimap2
make
```

This repository's Windows binary was built from unmodified upstream minimap2
2.31-r1302 source code in this environment.

## License

minimap2 is distributed under the MIT License.

This repository preserves the upstream minimap2 source and license.  
See the official minimap2 repository for the original source code and license
information:

https://github.com/lh3/minimap2

The release archive includes MSYS2 UCRT64 runtime DLLs.  
See [THIRD_PARTY_NOTICES.txt](THIRD_PARTY_NOTICES.txt) for third-party package
and license information.

## Disclaimer

This is a community build.

It is not provided, reviewed, or endorsed by the official minimap2 developers.  
Please verify the binaries and results in your own analysis environment.
