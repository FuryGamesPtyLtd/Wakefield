# Wakefield
Wakefield Unreal Engine Plugin - A C++ Extension Library For Unreal Engine.

## Installation

(1) Checkout the repository into the Plugins folder of your Unreal Engine Project:

    MyProject/
        MyProject.uproject
        Content/
           ...
        Source/
           ...
        Plugins/
            Wakefield/  <--- HERE
                Wakefield.uplugin
                Source/

(2) Add it to the `PrivateDepedencyModuleNames` list of your projects C++ module `.Build.cs` file:

    PrivateDependencyModuleNames.AddRange(new string[] { "Wakefield" });

You should now be able to `#include` the Wakefield headers in your C++ source files:

    #include "Wakefield/Print.h"

    /*...*/

    Print("Hello, World!");

## API

The Wakefield API provides the following headers:

### Header: `Wakefield/Print.h`

Provides the function `Print`:

    // Print(a1,a2,...,an) will convert its arguments to strings 
    // concatenate them with a space separator and UE_LOG them at
    // Display level.
    //
    // eg
    //
    //   Print("Hello, World!"); // will log "Hello, World!"
    //
    //   Print("The answer is", 42);  // will log "The answer is 42"

Provides the macro `WKF_PRINT_EXPR`:

    // WKF_PRINT_EXPR(expr) will stringize its argument expression
    // and its argument value and then Print("expr = value")
    //
    // eg
    //
    //   int NumCats = 42;
    //   WKF_PRINT_EXPR(NumCats); // will log "NumCats = 42"

### Header: `Wakefield/Enstring.h`

Provides the function `Enstring`:

    // Enstring(a1,a2,...,an) will convert its arguments to strings,
    // concatenate them, and return them as an FString.
    //
    // eg
    //    Enstring(42) returns FString("42")
    //    Enstring("a", "bc", 3) returns FString("abc3")

### Header: `Wakefield/ForEachObject.h`

Provides the function `ForEachObject` and the related `TFunction` instance type `FObjectVisitor`:

    // A FObjectVisitor is passed to ForEachObject as a parameter.
    //
    using FObjectVisitor = TFunction<void(UObject* Object)>;

    // ForEachObject calls ObjectVisitor once for each UObject instance
    // in the program, with the instance as parameter.
    //
    void ForEachObject(const FObjectVisitor& ObjectVisitor);

    // eg
    //
    //    ForEachObject([&](UObject* Object) {
    //         Print(Object->GetName());
    //    }); // prints the name of every UObject instance in the program.
