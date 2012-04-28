<Scene Name="ECDemo">
<Properties SystemType="Geometry">
  </Properties>

  <Properties SystemType="Graphics">
    <Property Name="AmbientLight" R="0.3" G="0.3" B="0.3"></Property>
    <!-- 
         Shadow Value1's:
         SHADOWTYPE_NONE             = 0
         SHADOWTYPE_TEXTURE_ADDITIVE = 33 
     -->
    <Property Name="Shadows" Value1="0" Value2="0"></Property>
    <Property Name="ShadowColor" R="0.67451" G="0.564706" B="0.403922"></Property>
    <Property Name="UseStaticGeom" Value1="0"/>
    <Property Name="UseInstancedGeom" Value1="1"/>
    <Property Name="FogColor" R="0.0" G="0.5" B="0.0"></Property>
	<!--
	   This is where we initialize the paged geometry system.  There are three sections that need to be in the .cdf in order (The .cdf
	   is loaded serially).  The first part is here, in the Graphics System.  It loads general information such as the height map, draw
	   distance and size of terrain.  These parameters will apply to all layers added to the system.  The second portion is in the camera
	   object, the third are the actual layer objects. The offset parameters adjust terrain calculations if the center of the terrain mesh
	   is not located at 0,0,0 in world coordinates.
	-->
	<!--
    <Property Name="PagedGeometry"  Heightmap="hp_terrain_heightmap_16bit_4096.png" ResourceGroup="farm_scene" Pagesize="500.0" Drawdistance="10000.0"></Property>
    <Property Name="PagedGeometryTerrain" Width="81072.1" Length="81686.7" Height="10254.9"></Property>
	<Property Name="PagedGeometryTerrainOffset" Width="0.0" Length="0.0" Height="-4879.6"></Property>
	-->
    <!--
      Mode - FOG_NONE   = 0
             FOG_EXP    = 1
             FOG_EXP2   = 2
             FOG_LINEAR = 3
             
      "Density" only applies to FOG_EXP and FOG_EXP2
      "Start" and "Stop" only apply to FOG_LINEAR
    -->
    <Property Name="Fog" Mode="0" Density="0.0001" Start="20000.0" Stop="35000.0"></Property>
    <Property Name="Font" FontPath="..//media//fonts" FontName="bluebold.ttf"/>
  </Properties>
  
  
 
  <Properties SystemType="Audio">
    <!-- Priority starts at 0 with highest -->
    <!-- Volume ranges from 0.0 (off) to 1.0 -->
  </Properties>
  <Properties SystemType="Input">
  </Properties>
  
  <Objects>
    <Object Name="MainCamera">
      <Properties SystemType="Geometry">
        <Property Name="Position" Value1="0.0" Value2="2.0" Value3="10.0"></Property>
      </Properties>
      <Properties SystemType="Graphics" ObjectType="Camera">
        <!-- The next line locks the camera to use the LookAt position instead of listening to the Input system -->
        <Property Name="LockCamera" Value1="1"/>
        <!-- Make the camera look at the house --> 
        <Property Name="LookAt" Value1="0" Value2="0" Value3="0"/>
        <Property Name="FOVy" Value1="0.523598"></Property>
        <Property Name="ClipDistances" Value1="5.0" Value2="120000.0"></Property>
        <!--
		   The next line (pagedgeometry) is required to associate the camera with the paged geometry module.  This
		   is the second of three parts.
		-->
        <!--<Property Name="PagedGeometry"></Property>-->
      </Properties>
      <Properties SystemType="Input" ObjectType="Overlay">
        <Property Name="Orientation" Value1="-0.89" Value2="0.2" Value3="0.0"/>
      </Properties>
      <!--Comment out this line to disable the CamBot!-->
      <!--<Properties SystemType="AI" ObjectType ="CamBot"></Properties>-->
      <Properties SystemType="Audio">
        <Property Name="Listener" Value1="1"/>
        <Property Name="Source" Value1="1"/>
        <Property Name="Position" Value1="0.0" Value2="1000.0" Value3="4000.0"/>
        <Property Name="SoundFile" Value1="DKC2_Enchanted_Woods_Dub.wav" Value2="Looping"/>
        <Property Name="Priority" Value1="0"/>
        <Property Name="Volume" Value1="0.03"/>
      </Properties>
    </Object>

	<!--
	   This is the third of three parts needed for the paged geometry.  Here, we are loading two grass layers into the system.
	   Some of the parameters are mandatory, others are not. Material is mandatory and tells the system which Ogre material to
	   use.  MapBounds is only mandatory if you are going to be using a density or colormap. It must come before you define those.
	   The Density field of the Density property is mandatory, the DensityMap field is not.  Please see the Paged Geometry
	   documentation for details on the other parameters.
	-->
	<!--
    <Object Name="GrassMaterial">
        <Properties SystemType="Graphics" ObjectType="PagedGeometryLayer">
            <Property Name="Material" Value1="GrassMaterial"/>
            <Property Name="MapBounds" Value1="-40536.05" Value2="-40843.35" Value3="40536.05" Value4="40843.35"/>
            <Property Name="MinSize" Width="200.0" Height="25.0"/>
            <Property Name="MaxSize" Width="300.0" Height="100.0"/>
            <Property Name="Animation" Enabled="0" Swaydistribution="0.01" Swaylength="8.0" Swayspeed="0.5"/>
            <Property Name="Density" Density=".0007" DensityMap="hp_terrain_density_grass.jpg"/>
            <Property Name="Color" Colormap="hp_terrain_lm.jpg"/>
            <Property Name="Render" Technique="0" Fade="0"/>
        </Properties>
    </Object>

    <Object Name="GrassMaterial2">
        <Properties SystemType="Graphics" ObjectType="PagedGeometryLayer">
            <Property Name="Material" Value1="GrassMaterial"/>
            <Property Name="MapBounds" Value1="-40536.05" Value2="-40843.35" Value3="40536.05" Value4="40843.35"/>
            <Property Name="MinSize" Width="50.0" Height="25.0"/>
            <Property Name="MaxSize" Width="90.0" Height="100.0"/>
            <Property Name="Animation" Enabled="1" Swaydistribution="0.01" Swaylength="8.0" Swayspeed="1.0"/>
            <Property Name="Density" Density=".0005" DensityMap="hp_terrain_density_grass.jpg"/>
            <Property Name="Color" Colormap="hp_terrain_lm.jpg"/>
        </Properties>
    </Object>
	-->

    <!-- Performance Windows -->
      <Object Name="StatWindow">
        <Properties SystemType="Graphics" ObjectType="StatWindow">
          <Property Name="Color" Value1="0" Value2="0" Value3="0" Value4="50"/>
          <Property Name="Position" Value1="0.01" Value2="0.23"/>
          <Property Name="Size" Value1="0.12" Value2="0.33"/>
        </Properties>
        <Properties SystemType="Input" ObjectType="Overlay">
          <Property Name="FKey" Value1="1" />
        </Properties>
      </Object>

      <Object Name="CPUChart">
        <Properties SystemType="Graphics" ObjectType="CPUChart">
          <Property Name="Color" Value1="0" Value2="0" Value3="0" Value4="50"/>
          <Property Name="Position" Value1="0.01" Value2="0.01"/>
          <Property Name="Size" Value1="0.3" Value2="0.2"/>
        </Properties>
        <Properties SystemType="Input" ObjectType="Overlay">
          <Property Name="FKey" Value1="2" />
        </Properties>
      </Object>

      <Object Name="WorkloadWindow">
        <Properties SystemType="Graphics" ObjectType="WorkloadWindow">
          <Property Name="Color" Value1="0" Value2="0" Value3="0" Value4="50"/>
          <Property Name="Position" Value1="0.76" Value2="0.01"/>
          <Property Name="Size" Value1="0.22" Value2="0.39"/>
        </Properties>
        <Properties SystemType="Input" ObjectType="Overlay">
          <Property Name="FKey" Value1="3" />
        </Properties>
      </Object>

    <!-- Lights -->
      <Object Name="Sun">
        <Properties SystemType="Graphics" ObjectType="Light">
          <Property Name="Type" Value1="Point"></Property>
          <Property Name="Position" Value1="-10359.527" Value2="25641.795" Value3="60803.297"></Property>
          <Property Name="Diffuse" R="0.862745" G="0.768628" B="0.607843"></Property>
          <Property Name="Specular" R="0.862745" G="0.768628" B="0.607843"></Property>
        </Properties>
      </Object>

    <!-- Sky -->
      <Object Name="sky">
        <Properties SystemType="Geometry">
          <Property Name="Position" Value1="0" Value2="2000" Value3="-0"/>
          <Property Name="Orientation" Value1="0" Value2="0" Value3="0" Value4="-1"/>
          <Property Name="Scale" Value1="1" Value2="1" Value3="1"/>
        </Properties>
        <Properties SystemType="Graphics" ObjectType="Mesh">
          <Property Name="Mesh" Value1="sky.mesh"/>
          <Property Name="CastShadows" Value1="0"/>
        </Properties>
      </Object>
			
			<Object Name="Level">
				<Properties SystemType="Geometry">
					<Property Name="Position" Value1="0" Value2="0" Value3="0"/>
					<Property Name="Orientation" Value1="0" Value2="0" Value3="0" Value4="1"/>
					<Property Name="Scale" Value1="1" Value2="1" Value3="1"/>
				</Properties>
				<Properties SystemType="Graphics" ObjectType="Mesh">
					<Property Name="Mesh" Value1="TestLevel.mesh"/>
					<Property Name="CastShadows" Value1="1"/>
				</Properties>
			</Object>
			
			<Object Name="player1">
				<Properties SystemType="Geometry">
					<Property Name="Position" Value1="0" Value2="0" Value3="0"/>
					<Property Name="Orientation" Value1="0" Value2="1.5707963267948966192313216916398" Value3="0" Value4="1"/>
					<Property Name="Scale" Value1="1" Value2="1" Value3="1"/>
				</Properties>
				<Properties SystemType="Graphics" ObjectType="MeshAnimated">
					<Property Name="Mesh" Value1="slash.mesh"/>
					<Property Name="CastShadows" Value1="1"/>
					<Property Name="Skeleton" Value1="slash.skeleton"/>
          <Property Name="Animation" Value1="run" Value2="running"/>
					<Property Name="Animation" Value1="idle" Value2="idle"/>
				</Properties>
				<Properties SystemType="Input">
					<!--<Property Name="Orientation" Value1="0.5" Value2="0.0" Value3="0.0"/>-->
				</Properties>
			</Object>
			
  </Objects>

<Links>
  <!--Links to hook the invisible water ball mesh to the camera which governs where the water impacted and extinguish burning elements.-->
  <!--<Link Subject="MainCamera" Observer="WaterBall" SubjectSystem="Graphics" ObserverSystem="Water"/><!--Get camera position and orientation updates-->
  <!--<Link Subject="MainCamera" Observer="WaterBall" SubjectSystem="Input" ObserverSystem="Water"/><!--Get hotkey event to turn fire impact element on/off-->

  <!--Links to hook the Ogre particle system to the camera for position and orientation updates.-->
  <!--<Link Subject="MainCamera" Observer="FireHose" SubjectSystem="Graphics" ObserverSystem="Graphics"/><!--Get camera position and orientation updates-->
  <!--<Link Subject="MainCamera" Observer="FireHose" SubjectSystem="Input" ObserverSystem="Graphics"/><!--Get hotkey event to turn fire hose visuals on/off-->
  <!--<Link Subject="MainCamera" Observer="FireHose" SubjectSystem="Graphics" ObserverSystem="Audio"/><!--Get camera position and orientation updates-->
  <!--<Link Subject="MainCamera" Observer="FireHose" SubjectSystem="Input" ObserverSystem="Audio"/><!--Get hotkey event to turn fire hose sound fx on/off-->
</Links>

</Scene>