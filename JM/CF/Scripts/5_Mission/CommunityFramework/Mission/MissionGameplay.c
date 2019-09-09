modded class MissionGameplay
{
	protected bool m_bLoaded;

	void MissionGameplay()
	{
		m_bLoaded = false;

		CreateModuleManager();
		
		GetRPCManager().AddRPC( "CF", "SetCFLogger", this, SingeplayerExecutionType.Client );

		GetRPCManager().AddRPC( "CF", "SendModList", this, SingeplayerExecutionType.Client );
	}

	void ~MissionGameplay()
	{
        DestroyModuleManager();
	}

	override void OnInit()
	{
		super.OnInit();
	}

	override void OnMissionStart()
	{
		super.OnMissionStart();

		GetModuleManager().ConstructModules( new JMModuleConstructor );
		GetModuleManager().RegisterModules();
		GetModuleManager().OnInit();
		GetModuleManager().ReloadSettings();
		GetModuleManager().OnMissionStart();
	}

	override void OnMissionFinish()
	{
		super.OnMissionFinish();

		GetModuleManager().OnMissionFinish();
	}

	void OnMissionLoaded()
	{
		GetModuleManager().OnMissionLoaded();
	}

	override void OnUpdate( float timeslice )
	{
		if ( !m_bLoaded && !GetDayZGame().IsLoading() )
		{
			m_bLoaded = true;
			OnMissionLoaded();
		}
		
		super.OnUpdate( timeslice );

		GetModuleManager().OnUpdate( timeslice );
	}
	
	void SetCFLogger( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
	{
		Param1< ref CFLogger > data;
		if ( type == CallType.Client && ctx.Read( data ) ) 
		{
			GetLogger().Copy( data.param1 );
			GetLogger().Update();
		}
	}

	void SendModList( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
	{
		Param1< autoptr map< string, string > > data;
		if ( type == CallType.Client && ctx.Read( data ) ) 
		{
			GetRPCManager().SendRPC( "CF", "RecieveModList", new Param1< autoptr map< string, string > >( ModLoader.GetModMetaData() ), false, NULL );
		}
	}
}
