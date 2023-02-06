CMake with Dynamic Libraries
============================

This is a simple executable with a DLL, that should output:

```
in main
in dll
```

Background
----------

For an executable that uses dynamic libraries to run, it must know where to
find the libraries.

Most so/dyllib/dll demonstrations have both things in one folder for simplicity.

This hides a pitfall, because the executable will find the dll if it is in
the same directory.

So: in the single-folder case, it works by happenstance.


Note
----

The commands shown are for Windows/Powershell, adjust accordingly for mac/linux.
I favored the Windows case here as the explicit '.exe' felt like it disambiguated.


Bring out your dynamics
-----------------------

Build the example as is; it fails to load, so there is no output.

```
> cmake -G Ninja -S . -B build-default
> cmake --build build-default
> ./build-default/main.exe
>
```

The DLL needs to be copied into the same directory as the executable
in order for the program to run.

Logically, this seems like a property of the DLL ("I need to go with
anyone who wants to link me")?

I added a conditional custom command to the dynamic target which
tests this, based on several guesses I found online:

```
> cmake -G Ninja -S . -B build-dynamic -DTEST_DYNAMIC_COPY=ON
> cmake --build build-dynamic
... errors ...
```

This fails because the generators produce empty strings, and what
the errors are hiding is a simple "copy\_if\_different expected arguments".

```
> cmake -G Ninja -S . -B build-main -DTEST_MAIN_COPY=ON
> cmake --build build-main
> ./build-main/main.exe
in main
in dll
>
```

Apparently, the onus is on the downstream consumer to know that it has dynamic
dependencies. Obvious in this trivial case but quickly lost in a chain of
dependencies.

A common pattern I see is people adding

```
# in the dylib's cmake
function (POST_BUILD_DYN_LIB TO_TARGET)
    add_custom_command ( ... )
endfunction ()


# in the consumer's post build
add_library (ConsumerLib consumer.cpp)
taret_link_libraries (ConsumerLib PUBLIC DynamicLib)
function (POST_BUILD_CONSUMER_LIB TO_TARGET)
    add_custom_command ( ... )
    # My responsibility to make this call.
    POST_BUILD_DYN_LIB (${TO_TARGET})
endfunction ()


# ... and so on

add_executable (Finally main.cpp)
target_link_libraries (Finally PUBLIC UpstreamOfConsumer)
POST_BUILD_UPSTREAM_OF_CONSUMER (Finally)
```
