# Github Actions

## TODO

-   Install R&S VISA on runners
-   Test VISA functionality in test_package or unit tests.

## Powershell

```shell
# Source URL
$url = "http://speed.transip.nl/10mb.bin"

# Destation file
$dest = "c:\temp\testfiles.bin"

# Download the file
Invoke-WebRequest -Uri $url -OutFile $dest
```

## macOS / Linux

```shell
curl -o newname.txt http://www.het.brown.edu/guide/UNIX-password-security.txt
```

## R&S VISA Downloads

| Operating System | Version | Link                                                                                                                            |
| ---------------- | ------- | ------------------------------------------------------------------------------------------------------------------------------- |
| Windows          | 7.2.2   | <https://scdn.rohde-schwarz.com/ur/pws/dl_downloads/dl_application/application_notes/1dc02___rs_v/RS_VISA_Setup_Win_7_2_2.exe>  |
| macOS            | 5.12.9  | <https://scdn.rohde-schwarz.com/ur/pws/dl_downloads/dl_application/application_notes/1dc02___rs_v/RS_VISA_Setup_MAC_5_12_9.pkg> |
| Ubuntu           | 5.12.9  | <https://scdn.rohde-schwarz.com/ur/pws/dl_downloads/dl_application/application_notes/1dc02___rs_v/rsvisa_5.12.9_amd64.deb>      |

Taken from [VISA and VISA Tools | Rohde & Schwarz](https://www.rohde-schwarz.com/us/driver-pages/remote-control/3-visa-and-tools_231388.html)
