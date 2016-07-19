
ArgumentParser::ArgumentParser (const juce::String& description)
    : mDescription (description)
    , mPrefixChars ("-")
{
    
}

void ArgumentParser::addArgument (ArgumentBase& argument)
{
    if (argument.isOptional())
    {
        for (auto name : argument.getNames())
        {
            // All optional argument names  must start with one of the parsers
            // prefix characters followed by an alpha character
            if ( ! isValidOptionalString (name))
                jassertfalse;
        }
        
        mOptionalArguments.add (&argument);
    }
    else if (argument.isPositional())
    {
        mPositionalArguments.add (&argument);
    }
}

void ArgumentParser::parseArgs (const juce::StringArray& args)
{
    if (parseKnownArgs (args).size())
    {
        // TODO: error unknown arguments
    }
}

juce::StringArray ArgumentParser::parseKnownArgs (const juce::StringArray& args)
{
    juce::StringArray unknownArgs = args;
    
    for (auto positionalArg : mPositionalArguments)
    {
        jassert (positionalArg);
        
        if (positionalArg)
            unknownArgs = positionalArg->parseKnownArgs (*this, unknownArgs);
    }
    
    for (auto optionalArg : mOptionalArguments)
    {
        jassert (optionalArg);
        
        if (optionalArg)
            unknownArgs = optionalArg->parseKnownArgs (*this, unknownArgs);
    }
    
    return unknownArgs;
}

juce::String ArgumentParser::getPrefixChars() const
{
    return mPrefixChars;
}

void ArgumentParser::setPrefixChars (const juce::String& chars)
{

}

bool ArgumentParser::isValidOptionalString (const juce::String& string) const
{
    for (int charIndex = 0; charIndex < mPrefixChars.length(); ++charIndex)
    {
        /*
        if (string.startsWithChar (mPrefixChars [charIndex])
            && string.removeCharacters (String (mPrefixChars [charIndex])).indexOfAnyOf ("abcdefghijklmnopqrstuvwxyz", 0, true) == 0)
        {
            return true;
        }
         */
    }
    
    return false;
}

//==============================================================================
//==============================================================================
#if JUCEY_UNIT_TESTS

class ArgumentParserTests : public juce::UnitTest
{
public:
    ArgumentParserTests() : UnitTest ("Argument Parser") {}
    
    void runTest() override
    {
        {
            OptionalArgument<juce::String>  stringArg           ("--string",    "-s");
            OptionalArgument<juce::String>  stringWithSpacesArg ("--string-ws", "-S");
            OptionalArgument<bool>          zeroArg             ("--zero",      "-z");
            OptionalArgument<bool>          oneArg              ("--one",       "-o");
            OptionalArgument<bool>          falseArg            ("--false",     "-f");
            OptionalArgument<bool>          trueArg             ("--true",      "-t");
            OptionalArgument<bool>          noArg               ("--no",        "-n");
            OptionalArgument<bool>          yesArg              ("--yes",       "-y");
            OptionalArgument<int>           intArg              ("--int",       "-i");
            OptionalArgument<juce::int64>   int64Arg            ("--int64",     "-I");
            OptionalArgument<float>         floatArg            ("--float",     "-F");
            OptionalArgument<double>        doubleArg           ("--double",    "-d");
            
            ArgumentParser parser;
            
            parser.addArgument (stringArg);
            parser.addArgument (stringWithSpacesArg);
            parser.addArgument (zeroArg);
            parser.addArgument (oneArg);
            parser.addArgument (falseArg);
            parser.addArgument (trueArg);
            parser.addArgument (noArg);
            parser.addArgument (yesArg);
            parser.addArgument (intArg);
            parser.addArgument (int64Arg);
            parser.addArgument (floatArg);
            parser.addArgument (doubleArg);
            
            {
                beginTest ("Argument Parser - long names");
                
                juce::StringArray args;
                args.add ("--string");
                args.add ("string");
                
                args.add ("--string-ws");
                args.add ("string with spaces");
                
                args.add ("--zero");
                args.add ("0");
                
                args.add ("--one");
                args.add ("1");
                
                args.add ("--false");
                args.add ("false");
                
                args.add ("--true");
                args.add ("true");
                
                args.add ("--no");
                args.add ("no");
                
                args.add ("--yes");
                args.add ("yes");
                
                args.add ("--int");
                args.add ("123");
                
                args.add ("--int64");
                args.add ("1234567890123456789");
                
                args.add ("--float");
                args.add ("3.14");
                
                args.add ("--double");
                args.add ("3.141592653589793238");
                
                parser.parseArgs (args);
                
                expect (stringArg.getValue() == "string");
                expect (stringWithSpacesArg.getValue() == "string with spaces");
                expect (zeroArg.getValue() == false);
                expect (oneArg.getValue() == true);
                expect (falseArg.getValue() == false);
                expect (trueArg.getValue() == true);
                expect (noArg.getValue() == false);
                expect (yesArg.getValue() == true);
                expect (intArg.getValue() == 123);
                expect (int64Arg.getValue() == 1234567890123456789);
                expect (floatArg.getValue() == 3.14f);
                expect (doubleArg.getValue() == 3.141592653589793238);
            }
            
            {
                beginTest ("Argument Parser - short names");
                
                juce::StringArray args;
                args.add ("-s");
                args.add ("STRING");
                
                args.add ("-S");
                args.add ("STRING WITH SPACES");
                
                args.add ("-z");
                args.add ("000");
                
                args.add ("-o");
                args.add ("001");
                
                args.add ("-f");
                args.add ("FALSE");
                
                args.add ("-t");
                args.add ("TRUE");
                
                args.add ("-n");
                args.add ("NO");
                
                args.add ("-y");
                args.add ("YES");
                
                args.add ("-i");
                args.add ("-123");
                
                args.add ("-I");
                args.add ("2234567890123456789");
                
                args.add ("-F");
                args.add ("-1.23");
                
                args.add ("-d");
                args.add ("1.1415926535897931");
                
                parser.parseArgs (args);
                
                expect (stringArg.getValue() == "STRING");
                expect (stringWithSpacesArg.getValue() == "STRING WITH SPACES");
                expect (zeroArg.getValue() == false);
                expect (oneArg.getValue() == true);
                expect (falseArg.getValue() == false);
                expect (trueArg.getValue() == true);
                expect (noArg.getValue() == false);
                expect (yesArg.getValue() == true);
                expect (intArg.getValue() == -123);
                expect (int64Arg.getValue() == 2234567890123456789);
                expect (floatArg.getValue() == -1.23f);
                expect (doubleArg.getValue() == 1.1415926535897931);
            }
        }
        
        ArgumentParser ("Process some integers.");
    }
    
};

static ArgumentParserTests argumentParserTests;

#endif // JUCEY_UNIT_TESTS
