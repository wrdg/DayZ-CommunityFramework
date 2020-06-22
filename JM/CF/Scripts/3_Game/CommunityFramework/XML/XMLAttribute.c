class XMLAttribute : Managed
{
    private string _name;
    private string _value;

    private XMLTag _parentTag;

    void XMLAttribute( ref XMLTag parent, string name )
    {
        _parentTag = parent;
        _name = name;
        _value = "";
    }

    void SetValue( string value )
    {
        _value = value;
    }

    string GetValue()
    {
        return _value;
    }

    string ValueAsString()
    {
        return _value;
    }

    bool ValueAsBool()
    {
        if ( _value == "true" )
            return true;

        return false;
    }

    int ValueAsInt()
    {
        return _value.ToInt();
    }

    float ValueAsFloat()
    {
        return _value.ToFloat();
    }

    vector ValueAsVector()
    {
        array<string> tokens = new array<string>;
        _value.Split( " ", tokens );

        return Vector( tokens[0].ToFloat(), tokens[1].ToFloat(), tokens[2].ToFloat() );
    }

    XMLTag GetParent()
    {
        return _parentTag;
    }

    void Debug( int level = 0 )
    {
        string indent = CF_Indent( level );
        Print( indent + " name=" + _name + " value=" + _value );
    }
};