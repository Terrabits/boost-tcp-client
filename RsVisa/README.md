# RsVisa

`RsVisa` contains object-oriented controls for a Rohde & Schwarz (R&S) ZNX-series Vector Network Analyzer (VNA) via a Virtual Instrument Software Architecture (VISA) connection and Standard Commands for Programmable Instruments (SCPI).

## Requirements

-   Microsoft Windows
-   Visual Studio 2017 with workload "Desktop Development with C++"
-   R&S VISA

## Classes

`RsVisa` provides two classes for controlling an instrument.

## Instrument

Header: `RsVisa/instrument.hpp`

`RsVisa::Instrument` is a class for controlling any general purpose instrument with VISA and SCPI.

### VISA

`RsVisa::Instrument` manages the VISA connection to the instrument.

The following methods load and unload the VISA shared library:

-   `RsVisa::Instrument::Instrument()`
-   `RsVisa::Instrument::~Instrument()`

The following methods manage the instrument connection:

-   `RsVisa::Instrument::isOpen()`
-   `RsVisa::Instrument::open()`
-   `RsVisa::Instrument::close()`
-   `RsVisa::Instrument::~Instrument()`

Note that the destructor will close the VISA connection if necessary.

The following methods manage the timeout time:

-   `RsVisa::Instrument::timeout_ms()`
-   `RsVisa::Instrument::setTimeout()`

The following methods are for basic string I/O:

-   `RsVisa::Instrument::read()`
-   `RsVisa::Instrument::write()`
-   `RsVisa::Instrument::query()`

The following methods are for binary I/O:

-   `RsVisa::Instrument::binaryRead()`
-   `RsVisa::Instrument::binaryWrite()`
-   `RsVisa::Instrument::binaryQuery()`

The following methods are for IEEE 488.2 Arbitrary Block Data:

-   `RsVisa::Instrument::readBlockData()`
-   `RsVisa::Instrument::queryBlockData()`

The following methods query the VISA connection status:

-   `RsVisa::Instrument::isError()`
-   `RsVisa::Instrument::status()`
-   `RsVisa::Instrument::statusMessage()`

### Common SCPI

It also contains methods that wrap common SCPI commands that apply to all general purpose instruments.

See methods:

| method                                              | SCPI Command |
| --------------------------------------------------- | ------------ |
| `RsVisa::Instrument::id()`                          | `*IDN?`      |
| `RsVisa::Instrument::options()`                     | `*OPT?`      |
| `RsVisa::Instrument::clearErrors()`                 | `*CLS`       |
| `RsVisa::Instrument::reset()`                       | `*RST`       |
| `RsVisa::Instrument::wait()`                        | `*WAI`       |
| `RsVisa::Instrument::isOperationComplete()`         | `*OPC`       |
| `RsVisa::Instrument::blockUntilOperationComplete()` | `*OPC?`      |

### Example

For an example demonstrating basic use of `RsVisa::Instrument`, see `examples/instrument.cpp`.

## Znx

Header: `RsVisa/znx.hpp`

`RsVisa::Znx` is a class for controlling a R&S ZNX-series VNA with VISA and SCPI.

It publicly inherits from `RsVisa::Instrument`, and therefore exposes its functionality.

It also implements specific ZNX-series SCPI commands.

### Data Format

The `RsVisa::DataFormat` class provides object-oriented control of the data transfer format.

This class can be accessed from the method:

`RsVisa::Znx::dataFormat()`

#### ASCII

The following methods are relevant to the ASCII data format:

-   `RsVisa::DataFormat::isAscii()`
-   `RsVisa::DataFormat::setAscii()`

#### 32-bit Float

The following methods are relevant to the 32-bit floating point data format:

-   `RsVisa::DataFormat::isBinary32Bit()`
-   `RsVisa::DataFormat::setBinary32Bit()`
-   `RsVisa::DataFormat::isBigEndian()`
-   `RsVisa::DataFormat::setBigEndian()`
-   `RsVisa::DataFormat::isLittleEndian()`
-   `RsVisa::DataFormat::setLittleEndian()`

#### 64-bit Float

The following methods are relevant to the 64-bit floating point data format (i.e. C++ `double`):

-   `RsVisa::DataFormat::isBinary64Bit()`
-   `RsVisa::DataFormat::setBinary64Bit()`
-   `RsVisa::DataFormat::isBigEndian()`
-   `RsVisa::DataFormat::setBigEndian()`
-   `RsVisa::DataFormat::isLittleEndian()`
-   `RsVisa::DataFormat::setLittleEndian()`

### Display

The `RsVisa::Display` class provides object-oriented control of the ZNX display.

This class can be accessed from the method:

`RsVisa::Znx::display()`

#### On/Off

The following methods turn display updates on or off:

-   `RsVisa::Display::isOn()`
-   `RsVisa::Display::setOn()`
-   `RsVisa::Display::setOff()`

#### Manual Update

The ZNX display can be manually updated. The following methods control manual update:

-   `RsVisa::Display::isManualUpdate()`
-   `RsVisa::Display::setManualUpdate()`
-   `RsVisa::Display::update()`

#### Remote Mode

The ZNX-series VNA starts in Local Mode. In this state, all functionality in the graphical user interface (GUI) is available to the end-user.

When a VISA connection is made with the instrument, the instrument puts itself into Remote Mode. In Remote Mode, the user's interaction with the VNA via the GUI is limited.

Sometimes it is necessary to control the mode, e.g. to put the instrument into Local Mode to facility user interaction.

The following methods control the Local and Remote modes:

-   `RsVisa::Display::local()`
-   `RsVisa::Display::remote()`

### Channels

The ZNX-series VNA can contain many measurement channels, each with its own independent measurement setup.

Channels are typically referenced by the index (e.g. index `1` for channel 1).

#### Life Cycle

The following methods control the life cycle of channels:

-   `RsVisa::Znx::isChannel()`
-   `RsVisa::Znx::channels()`
-   `RsVisa::Znx::createChannel()`

#### Channel

The `RsVisa::Channel` class provides object-oriented control of measurement channels.

This class can be accessed from the method:

`RsVisa::Znx::channel()`

The following methods control channel measurement settings:

-   `RsVisa::Channel::points()`
-   `RsVisa::Channel::setPoints()`
-   `RsVisa::Channel::startFrequency_Hz()`
-   `RsVisa::Channel::setStartFrequency()`
-   `RsVisa::Channel::stopFrequency_Hz()`
-   `RsVisa::Channel::setStopFrequency()`
-   `RsVisa::Channel::frequencies_Hz()`

### Traces

The ZNX-series VNA can contain many measurement traces. Traces are typically referenced by name (e.g. `Trc1`). Each trace has a parameter and format (e.g. parameter `S21` and format `MLOG` [log magnitude]).

#### Life Cycle

The following methods control the life cycle of traces:

-   `RsVisa::Znx::isTrace()`
-   `RsVisa::Znx::traces()`
-   `RsVisa::Znx::createTrace()`

#### Trace

The `RsVisa::Trace` class provides object-oriented control of traces.

This class can be accessed from the method:

`RsVisa::Znx::trace()`

The following methods control the active trace:

-   `RsVisa::Trace::select()`

The following methods control the trace settings:

-   `RsVisa::Trace::parameter()`
-   `RsVisa::Trace::setParameter()`
-   `RsVisa::Trace::format()`
-   `RsVisa::Trace::setFormat()`
-   `RsVisa::Trace::diagram()`
-   `RsVisa::Trace::setDiagram()`

The following methods retrieve formatted and unformatted measurement values, respectively:

-   `RsVisa::Trace::y()`
-   `RsVisa::Trace::y_complex()`

### Example

For an example demonstrating basic use of `RsVisa::Znx`, see `examples/znx.cpp`.
