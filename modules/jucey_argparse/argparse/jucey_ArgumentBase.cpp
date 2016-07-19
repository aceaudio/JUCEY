
ArgumentBase::ArgumentBase (const juce::StringArray& names)
    : mNames (names)
    , mNumberOfArguments (kDefault)
    , mIsRequired (false)
{
    
}

juce::StringArray ArgumentBase::getNames() const
{
    return mNames;
}

void ArgumentBase::setNumberOfArguments (int numberOfArguments)
{
    mNumberOfArguments = numberOfArguments;
}

int ArgumentBase::getNumberOfArguments() const
{
    return mNumberOfArguments;
}

void ArgumentBase::addName (const juce::String& name)
{
    mNames.add (name);
}

void ArgumentBase::setRequired (bool isRequired)
{
    mIsRequired = isRequired;
}

bool ArgumentBase::isRequired() const
{
    return mIsRequired;
}