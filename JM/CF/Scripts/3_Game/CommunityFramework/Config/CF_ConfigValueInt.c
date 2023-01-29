typedef CF_ConfigValueInt ConfigValueInt;

class CF_ConfigValueInt : CF_ConfigValue
{
	private int _value;

	override string GetType()
	{
		return "INT";
	}

	override bool IsInt()
	{
		return true;
	}

	override int GetInt()
	{
		return _value;
	}

	override void SetInt(int value)
	{
		_value = value;
	}
};
