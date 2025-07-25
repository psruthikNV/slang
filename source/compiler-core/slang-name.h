// slang-name.h
#ifndef SLANG_NAME_H_INCLUDED
#define SLANG_NAME_H_INCLUDED

// This file defines the `Name` type, used to represent
// the name of types, variables, etc. in the AST.

#include "../core/slang-basic.h"

namespace Slang
{

// The `Name` type is used to represent the name of a type, variable, etc.
//
// The key benefit of using `Name`s instead of raw strings is that `Name`s
// can be compared for equality just by testing pointer equality. Names
// also don't require any memory management; you can just retain an ordinary
// pointer to one and not deal with reference-counting overhead.
//
// In order to provide these benefits, a `Name` can only be created using
// a `NamePool` that owns the allocations for all the names (so they get
// cleaned up when the pool is deleted), and which is responsible for
// ensuring the uniqueness of name objects.
//
class Name : public RefObject
{
public:
    // The raw text of the name.
    //
    // Note that at some point in the future we might have other categories
    // of name than "simple" names, and so this might change to a structured
    // ADT instead of a simple string.
    String text;
};

// Get the textual string representation of a name
// (e.g., so that it can be printed).
String getText(Name* name);

/// Get the text as unowned string slice
UnownedStringSlice getUnownedStringSliceText(Name* name);

// Get a name as a C style string, or nullptr if name is nullptr
const char* getCstr(Name* name);

// A `NamePool` is used to store and look up names.
// If two systems need to work together with names, and be sure that they
// get equivalent names for a string like `"Foo"`, then they need to use
// the same name pool (directly or indirectly).
//
struct NamePool
{
    // Find or create the `Name` that represents the given `text`.
    Name* getName(UnownedStringSlice text);
    Name* getName(String const& text);
    // Try find the `Name` that represents the given `text`.
    // If the name does not exist, return nullptr
    Name* tryGetName(String const& text);

    // The mapping from text strings to the corresponding name.
    Dictionary<String, RefPtr<Name>> names;
};

} // namespace Slang

#endif
