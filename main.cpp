////////////////////////////////////////////////////////////////////////////////
//																			 	
// 	todo : Mouse movement with cursor.
//
//	Semi done, buggy :|. Node not translating to cursor position.
//
//	Ogre::Real x = ms.X.abs; Abs = absolute.
//	Ogre::Real y = ms.Y.abs;
//
// 	Tried turning the x,y into float for direction.
//	Minute better, still buggy. Work on me asap.
//	todo :
// 	Create a new node called "moveme" thats invisable.
//	When you left click within the world grab x,y,z of cursor coordinates.    
//
//	First move "moveme" to those coordinates.
//	Then move the "Character" and "camera" to "moveme" node coordinates.
//	SET animation state (Run)
//	Perform a update check on location of moveme and player coordinates.
//	IF both "character" and "moveme" coordinates are the same. jump to *
//	OR else! just incase you have bumped into an object.
//	IF "Character" speed = 0;
//	After passed time. 
//	* STOP "character" movement.
//	SET animation state (idle)
//	IF left mouse button click and within radius of "moveme" node
//	and speed = 0; save mouse coordinates.
//	Perform a check for what is at the mouse coordinates.
//	IF item/useable object
//	Perform Action. (Pickup/pull/push/ect)
//
//	Collision will not effect camera follow because of the speed Variable.
//	The camera will want to translate and can BUT speed will be 0. =)
//
//	Thoughts:-
//
//	Can i use static geometry creation for ground ( Will it effect physics?)
//	If i can use the method below to spawn generic land.
//	Instead of the really bad grass. 
//
//	So set my entire map using the static geometry and use
//	all name "map_1" then once i have it in code and origins setup.
//	just call map_1->build();
//
//	Could also use a progress bar for the build queue code.
//
//	Need imgui for visual feed back for Variables/node locations/states/ect.
//	Miss me gui ^_^.
// 																	
//////////////////////////////////////////////////////////////////////////////
//
// Includes
//
#include "OGRE/Ogre.h"
#include "OIS.h"
//////////////////////////////////////////////////////////////////////////////
// 
// Constant values - Place these into a header file.
//
//
float 	SpeedChange = 0.10;
float 	Radians = 0.10;
//////////////////////////////////////////////////////////////////////////////
//
// Working Variables
//
bool 	Move = true;
bool	AIon = true;
float 	Speed = 0.0f;
float 	Direction = 1.60f;
float	LastDirection = 0.0f;
float 	WalkSpeed = 1;
float 	WalkSpeed2 = 1.0f;
float	Directiontoface = 1.60f;
float 	WalkSpeed3 = 0.90f;
float	X = 0;
float   Y = 0;
/////////////////////////////////////////////////////////////////////////////

int main()
{

////////////////////////////////////////////////////////////////////////////
//
//	Setup plugins/Root/window/input manager/keyboard/mouse/scene manager
//	camera.
//	
	Ogre::String lConfigFileName = "";
	Ogre::String lPluginsFileName = "";
	Ogre::String lLogFileName = "Important_information.LOG";
	std::auto_ptr<Ogre::Root> lRoot(
	new Ogre::Root(lConfigFileName, lPluginsFileName, lLogFileName));
	{	
	typedef std::vector<Ogre::String> Setup;
	Setup lPluginNames;
	lPluginNames.push_back("RenderSystem_GL");
	lPluginNames.push_back("Plugin_ParticleFX");
	lPluginNames.push_back("Plugin_CgProgramManager");
	lPluginNames.push_back("Plugin_PCZSceneManager");
	lPluginNames.push_back("Plugin_OctreeZone");
	lPluginNames.push_back("Plugin_OctreeSceneManager");
	Setup::iterator lIter = lPluginNames.begin();
	Setup::iterator lIterEnd = lPluginNames.end();
		for(;lIter != lIterEnd; lIter++)
		{
			Ogre::String& lPluginName = (*lIter);
			lRoot->loadPlugin(lPluginName);
		}
	
	}

	{
	const Ogre::RenderSystemList& lRenderSystemList = lRoot->getAvailableRenderers();
	Ogre::RenderSystem *lRenderSystem = lRenderSystemList[0];
	lRoot->setRenderSystem(lRenderSystem);
	}
	{
	bool lCreateAWindowAutomatically = false;
	Ogre::String lWindowTitle = "";
	Ogre::String lCustomCapacities = "";
	lRoot->initialise(lCreateAWindowAutomatically, lWindowTitle, lCustomCapacities);
	}
	Ogre::RenderWindow* lWindow = NULL;
	{
	Ogre::String lWindowTitle = "First setup 0.1 WIP";
	unsigned int lSizeX = 800;
	unsigned int lSizeY = 600;
	bool lFullscreen = false; 
	Ogre::NameValuePairList lParamswindow;
	lParamswindow["FSAA"] = "0"; 
	lParamswindow["vsync"] = "true";
	lWindow = lRoot->createRenderWindow(lWindowTitle, lSizeX, lSizeY, lFullscreen, &lParamswindow);
	}

	
	Ogre::SceneManager* lScene = lRoot->createSceneManager(Ogre::ST_GENERIC, "BasicSceneManager");
	Ogre::SceneNode* lRootSceneNode = lScene->getRootSceneNode();
	Ogre::Camera* lCamera = lScene->createCamera("ViewMeCamera");
	Ogre::SceneNode* lCameraNode = lRootSceneNode->createChildSceneNode("CameraNode1");
	lCameraNode->attachObject(lCamera);
	float lViewportWidth = 0.99f;
	float lViewportHeight = 0.99f;
	float lViewportLeft	= (1.0f - lViewportWidth) * 0.5f;
	float lViewportTop = (1.0f - lViewportHeight) * 0.5f;
	unsigned short lMainViewportZOrder = 100;
	Ogre::Viewport * vp = lWindow->addViewport(lCamera, lMainViewportZOrder, lViewportLeft, lViewportTop, lViewportWidth, lViewportHeight);
	vp->setAutoUpdated(true);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	float ratio = float(vp->getActualWidth()) / float(vp->getActualHeight());
	lCamera->setAspectRatio(ratio);
	lCamera->setNearClipDistance(1.5f);
	lCamera->setFarClipDistance(3000.0f);
	lCamera->pitch(Ogre::Degree (90));
	lCamera->setFixedYawAxis (true);
	lCamera->setPosition(Ogre::Vector3(200,400,200));
	lCamera->lookAt(Ogre::Vector3(0,20,0));
	lWindow->setActive(true);
	lWindow->setAutoUpdated(false);
	lScene->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	
	OIS::ParamList lparamsois;
	lparamsois.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	lparamsois.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	lparamsois.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
    lparamsois.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
	lWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	lparamsois.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
	OIS::Keyboard* lKeyboard = NULL;
	OIS::Mouse* lMouse = NULL;
	OIS::InputManager* lInputManager = OIS::InputManager::createInputSystem( lparamsois );
	lKeyboard = static_cast<OIS::Keyboard*>(lInputManager->createInputObject(OIS::OISKeyboard, false));
	lMouse = static_cast<OIS::Mouse*>(lInputManager->createInputObject(OIS::OISMouse, false));
	unsigned int width = 800; 
	unsigned int height = 600;
	unsigned int depth = 0;
	int top = 0.06;
	int left = 0.06;
	lWindow->getMetrics(width, height, depth, left, top);
	const OIS::MouseState &ms = lMouse->getMouseState();
	ms.width = width;
	ms.height = height;
	
	

	
////////////////////////////////////////////////////////////////////////////
//
//	Level 0 resource loading. this could also be pointed to a .zip file :)
//
//	Means i can load levels individually and unload them as well.
//	Switch/case for level select. 
//
	Ogre::String lNameOfResourceGroup = "First go";
	
	Ogre::ResourceGroupManager& lMystuff = Ogre::ResourceGroupManager::getSingleton();
	lMystuff.createResourceGroup(lNameOfResourceGroup);
	Ogre::String lDirectoryToLoad = "C:/Users/Luke/Desktop/ogre/ogre.1.8.1";

	bool lIsRecursive = false;
	lMystuff.addResourceLocation(lDirectoryToLoad, "FileSystem", lNameOfResourceGroup, lIsRecursive);
	lMystuff.initialiseResourceGroup(lNameOfResourceGroup);
	lMystuff.loadResourceGroup(lNameOfResourceGroup);
	
/////////////////////////////////////////////////////////////////////////////
//
//	Setting up meshs/static geometry/particles for level 0
//
/////////////////////////////////////////////////////////////////////////////
//
//	Player model.
//
	Ogre::Entity* ogreHead = lScene->createEntity("Head", "ogrehead.mesh");
	Ogre::SceneNode* headNode = lScene->getRootSceneNode()->createChildSceneNode("HeadNode",Ogre::Vector3( 0, 20, 0 ));
	headNode->attachObject(ogreHead);
	headNode->translate(0, 0, 0);
	ogreHead->setMaterialName("BeachStones");
	lCamera->setAutoTracking (true, headNode);
	
////////////////////////////////////////////////////////////////////////////
//
//	Level details.
//	
	Ogre::Light* Lights = lScene->createLight("me");
	Lights->setType(Ogre::Light::LT_SPOTLIGHT);
	Lights->setDiffuseColour(1.0, 1.0, 1.0);
	Lights->setSpecularColour(1.0, 1.0, 1.0);
	Lights->setDirection(20, -2, 20);
	Lights->setPosition(0, 250.0, 0);
	Lights->setSpotlightRange(Ogre::Degree(260), Ogre::Degree(260));
	
	Ogre::Entity* land = lScene->createEntity("land", "Garden.mesh");
	Ogre::SceneNode* landNode = lScene->getRootSceneNode()->createChildSceneNode("landNode",Ogre::Vector3( 0, 1, 0 ));
	landNode->attachObject(land);
	landNode->translate(0, 0, 0);
	landNode->scale( 40, 40, 40 );
	
	Ogre::Entity* land1 = lScene->createEntity("land1", "Garden.mesh");
	Ogre::SceneNode* landNode1 = lScene->getRootSceneNode()->createChildSceneNode("landNode1",Ogre::Vector3( 0, 1, 0 ));
	landNode1->attachObject(land1);
	landNode1->translate(640, 0, 0);
	landNode1->scale( 40, 40, 40 );
	
//	Ogre::ManualObject* manual = lScene->createManualObject("grass");
//	manual->begin("GrassBlades", Ogre::RenderOperation::OT_TRIANGLE_LIST);
//	manual->position(5.0, 0.0, 0.0);
//	manual->textureCoord(1,1);
//	manual->position(-5.0, 10.0, 0.0);
//	manual->textureCoord(0,0);
//	manual->position(-5.0, 0.0, 0.0);
//	manual->textureCoord(0,1);
//	manual->position(5.0, 10.0, 0.0);
//	manual->textureCoord(1,0);
//	manual->position(2.5, 0.0, 4.3);
//	manual->textureCoord(1,1);
//	manual->position(-2.5, 10.0, -4.3);
//	manual->textureCoord(0,0);
//	manual->position(-2.0, 0.0, -4.3);
//	manual->textureCoord(0,1);
//	manual->position(2.5, 10.0, 4.3);
//	manual->textureCoord(1,0);
//	manual->position(2.5, 0.0, -4.3);
//	manual->textureCoord(1,1);
//	manual->position(-2.5, 10.0, 4.3);
//	manual->textureCoord(0,0);
//	manual->position(-2.0, 0.0, 4.3);
//	manual->textureCoord(0,1);
//	manual->position(2.5, 10.0, -4.3);
//	manual->textureCoord(1,0);
//	manual->index(0);
//	manual->index(1);
//	manual->index(2);
//	manual->index(0);
//	manual->index(3);
//	manual->index(1);
//	manual->index(4);
//	manual->index(5);
//	manual->index(6);
//	manual->index(4);
//	manual->index(7);
//	manual->index(5);
//	manual->index(8);
//	manual->index(9);
//	manual->index(10);
//	manual->index(8);
//	manual->index(11);
//	manual->index(9);
//	manual->end();
//	manual->convertToMesh("GrassBlades");
//	
//	// Play with me more :p Should be able to use this to spawn map.
//	Ogre::StaticGeometry* field = lScene->createStaticGeometry("FieldOfGrass");
//	for(int i=0;i<6;i++)
//		{
//			for(int j=0;j<6;j++)
//			{
//				Ogre::Entity * ent = lScene->createEntity("GrassBlades");
//				field->addEntity(ent,Ogre::Vector3(i*-40,-30,j*-40),Ogre::Quaternion::IDENTITY,Ogre::Vector3(8,8,8));
//				
//			}
//		}
//	
//	field->build();
//	field->setVisible(true);
//	
//	
//	Ogre::SceneNode* Lightswitchnode = lScene->createSceneNode("Node1");
//	lScene->getRootSceneNode()->addChild(Lightswitchnode);
//	
//	Ogre::Light* light1 = lScene->createLight("Light1");
//	light1->setType(Ogre::Light::LT_POINT);
//	
//	light1->setPosition(-120,40,50);
//	light1->setDiffuseColour(1.0f,1.0f,0.0f);
//
//	Ogre::Entity* LightEnt = lScene->createEntity("MyEntity","Sphere.mesh");
//	Ogre::SceneNode* node3 = Lightswitchnode->createChildSceneNode("node3");
//	node3->setScale(0.1f,0.1f,0.1f);
//	node3->translate(0, 0, 0);
//	node3->scale( 100, 100, 100 );
//	node3->setPosition(-120,40,50);
//	node3->attachObject(LightEnt);
//	
//	Ogre::SceneNode* Lightswitchnode2 = lScene->createSceneNode("Node2");
//	lScene->getRootSceneNode()->addChild(Lightswitchnode2);
//	
//	Ogre::Light* light2 = lScene->createLight("Light2");
//	light2->setType(Ogre::Light::LT_POINT);
//	
//	light2->setPosition(120,40,50);
//	light2->setDiffuseColour(0.0f,1.0f,0.0f);
//
//	Ogre::Entity* LightEnt2 = lScene->createEntity("MyEntity2","Sphere.mesh");
//	Ogre::SceneNode* node2 = Lightswitchnode->createChildSceneNode("node2");
//	node2->setScale(0.1f,0.1f,0.1f);
//	node2->translate(0, 0, 0);
//	node2->scale( 100, 100, 100 );
//	node2->setPosition(120,40,50);
//	node2->attachObject(LightEnt2);
//	LightEnt2->setMaterialName("02_-_Default");
//	
//	Ogre::SceneNode* Lightswitchnode5 = lScene->createSceneNode("Node5");
//	lScene->getRootSceneNode()->addChild(Lightswitchnode5);
//	
//	Ogre::Light* light5 = lScene->createLight("Light5");
//	light5->setType(Ogre::Light::LT_POINT);
//	
//	light5->setPosition(0,40,200);
//	light5->setDiffuseColour(0.0f,0.0f,1.0f);
//
//	Ogre::Entity* LightEnt5 = lScene->createEntity("MyEntity5","Sphere.mesh");
//	Ogre::SceneNode* node5 = Lightswitchnode->createChildSceneNode("node5");
//	node5->setScale(0.1f,0.1f,0.1f);
//	node5->translate(0, 0, 0);
//	node5->scale( 100, 100, 100 );
//	node5->setPosition(0,40,200);
//	node5->attachObject(LightEnt5);
//	LightEnt5->setMaterialName("03_-_Default");
//	
//	
//	Ogre::ParticleSystem* partSystem = lScene->createParticleSystem("Aureola","Examples/Aureola");
//	Ogre::Entity* pent1 = lScene->createEntity("pent1", "Sphere.mesh");
//	Ogre::SceneNode* pnode1 = lScene->getRootSceneNode()->createChildSceneNode("pnode1");
//	pnode1->setPosition(-120,40,50);
//	pnode1->translate(0, 1, 0);
//	pnode1->attachObject(pent1);
//	pnode1->attachObject(partSystem);
//	pnode1->setVisible(true);
//	
//	Ogre::ParticleSystem* partSystem2 = lScene->createParticleSystem("PurpleFountain","Examples/PurpleFountain");
//	Ogre::Entity* pent2 = lScene->createEntity("pent2", "Sphere.mesh");
//	Ogre::SceneNode* pnode2 = lScene->getRootSceneNode()->createChildSceneNode("pnode2");
//	pnode2->setPosition(120,40,50);
//	pnode2->translate(0, 1, 0);
//	pnode2->attachObject(pent2);
//	pnode2->attachObject(partSystem2);
//	pnode2->setVisible(true);
//	
//	Ogre::ParticleSystem* partSystem3 = lScene->createParticleSystem("GreenyNimbus","Examples/GreenyNimbus");
//	Ogre::Entity* pent3 = lScene->createEntity("pent3", "Sphere.mesh");
//	Ogre::SceneNode* pnode3 = lScene->getRootSceneNode()->createChildSceneNode("pnode3");
//	pnode3->setPosition(0,40,200);
//	pnode3->translate(0, 1, 0);
//	pnode3->attachObject(pent3);
//	pnode3->attachObject(partSystem3);
//	pnode3->setVisible(true);
	Ogre::Entity* Moveme = lScene->createEntity( "Moveme", "ogrehead.mesh" );
	Ogre::SceneNode* MMNODE = lScene->getRootSceneNode()->createChildSceneNode("Moveme", Ogre::Vector3( 0, 20, 0 ) );
	MMNODE->attachObject(Moveme);
	MMNODE->translate(0, 0, 0);
//	mechNode2->yaw( Ogre::Degree( -90 ) );
	Moveme->setMaterialName("BeachStones");
	//MMNODE->setVisible(true);

	Ogre::Entity* Goalkeeper = lScene->createEntity( "Keeper", "ogrehead.mesh" );
	Ogre::SceneNode* KNODE1 = lScene->getRootSceneNode()->createChildSceneNode("Keeper", Ogre::Vector3( 0, 20, 0 ) );
	KNODE1->attachObject(Goalkeeper);
	KNODE1->translate(0, 0, 0);
//	mechNode2->yaw( Ogre::Degree( -90 ) );
	Goalkeeper->setMaterialName("BeachStones");
	Ogre::Vector3 Start = KNODE1->getPosition();
	
	Ogre::Entity* Goalkeeper2 = lScene->createEntity( "Keeper2", "ogrehead.mesh" );
	Ogre::SceneNode* KNODE2 = lScene->getRootSceneNode()->createChildSceneNode("Keeper2", Ogre::Vector3( -280, 20, 0 ) );
	KNODE2->attachObject(Goalkeeper2);
	KNODE2->translate(0, 0, 0);
	KNODE2->yaw( Ogre::Degree( 90 ) );
	Goalkeeper2->setMaterialName("BeachStones");
	
	
	Ogre::Entity* Goalkeeper3 = lScene->createEntity( "Keeper3", "ogrehead.mesh" );
	Ogre::SceneNode* KNODE3 = lScene->getRootSceneNode()->createChildSceneNode("Keeper3", Ogre::Vector3( 280, 20, 0 ) );
	KNODE3->attachObject(Goalkeeper3);
	KNODE3->translate(0, 0, 0);
	KNODE3->yaw( Ogre::Degree( 270) );
	Goalkeeper3->setMaterialName("BeachStones");
	

//	
//	Ogre::Entity* athene = lScene->createEntity( "athene", "athene.mesh" );
//	Ogre::SceneNode* atheneNode = lScene->getRootSceneNode()->createChildSceneNode("athene", Ogre::Vector3( -60, 20, 0 ) );
//	atheneNode->attachObject(athene);
//	atheneNode->translate(0, 0, 0);
//	atheneNode->scale( -0.5, -0.5, -0.5 );
//	atheneNode->yaw( Ogre::Degree( -360 ) );
//	atheneNode->pitch( Ogre::Degree( -180 ) );
//	athene->setMaterialName("MRAMOR-bump");
//	
//	Ogre::Entity* house = lScene->createEntity("House", "house.mesh");
//	Ogre::SceneNode* houseNode = lScene->getRootSceneNode()->createChildSceneNode("HouseNode",Ogre::Vector3( 130, 0, -200 ) );
//	houseNode->attachObject(house);
//	houseNode->translate(0, 0, 0);
//	houseNode->scale( 100, 100, 100 );
//	ogreHead->setMaterialName("BeachStones");
	
	
 
	
	
//	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -1);
//
//	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
//	plane, 400, 400, 40, 40, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
//
//	Ogre::Entity* Ground = lScene->createEntity("GroundEntity", "ground");
//	lScene->getRootSceneNode()->createChildSceneNode()->attachObject(Ground);
//
//	Ground->setMaterialName("BumpyMetal");
//	Ground->setCastShadows(false);

///////////////////////////////////////////////////////////////////////////
//
//	Rendering loop/capture loop. imgui source here..
//	
	lRoot->clearEventTimes();


	Ogre::Timer Stepper3;
	Ogre::Timer Stepper2;
	Ogre::Timer Stepper;
	Ogre::Timer AI;
	Ogre::Timer End;
	while(!lWindow->isClosed())
	{
		lWindow->update(false);
		bool lVerticalSynchro = true;
		lWindow->swapBuffers(lVerticalSynchro);
		lRoot->renderOneFrame();
		lMouse->capture();
		if(ms.buttonDown(OIS::MB_Left))
		{
			//if (Stepper3.getMilliseconds() > 250)
			//{
			
			//int x = ms.X;
			//Ogre::Vector3 (ms.X.abs,0,ms.Y.abs);
			Ogre::Real x = ms.X.abs;
			Ogre::Real y = ms.Y.abs;
			
			float newd = 0.0f;
			newd = x + y; //converted to float
			
			MMNODE->translate(Ogre::Vector3(Ogre::Math::Cos(newd),0,Ogre::Math::Sin(newd)) * WalkSpeed3);
			//}
		}

		lKeyboard->capture();
		if (lKeyboard->isKeyDown(OIS::KC_A))
		{
			Ogre::LogManager::getSingleton().logMessage("*~*~*KEYBOARD!!!");
		}
		
		if (lKeyboard->isKeyDown(OIS::KC_UP)) 
		{
		if (Speed<5) Speed+=SpeedChange;
		} 
		else if (lKeyboard->isKeyDown(OIS::KC_DOWN)) 
		{
		if (Speed>0) Speed-=SpeedChange;
		}

		if (Speed>=0) 
		{
		if (lKeyboard->isKeyDown(OIS::KC_RIGHT))
		{
			Direction += Radians;
			headNode->yaw(Ogre::Radian(-Radians));
		} 
		else if (lKeyboard->isKeyDown(OIS::KC_LEFT))	
	
		{
			Direction -= Radians;
			headNode->yaw(Ogre::Radian(Radians));
		}		
		if (Speed>0) 
		{
			headNode->translate(Ogre::Vector3(Ogre::Math::Cos(Direction),0,Ogre::Math::Sin(Direction)) * Speed);
			lCameraNode->translate(Ogre::Vector3(Ogre::Math::Cos(Direction),0,Ogre::Math::Sin(Direction)) * Speed);
		}
		
		}
			
/////////////////////////////////////////////////////////////////////////////
//
//	Simple node translating using a timer.
//			
	if (Move = true)
			{
				
				if (Stepper.getMilliseconds() >= 2000 && Directiontoface == 1.60f)
				{
					WalkSpeed = 1;
					KNODE1->translate(Ogre::Vector3(Ogre::Math::Cos(Directiontoface),0,Ogre::Math::Sin(Directiontoface)) * WalkSpeed);
				}
				if (Stepper.getMilliseconds() >= 4500 && Directiontoface == 1.60f)
				{
					WalkSpeed = 0;
					Directiontoface = 0.00f;
					KNODE1->yaw(Ogre::Degree(90));
					Stepper.reset();
				}
				if (Stepper.getMilliseconds() >= 2000 && Directiontoface == 0.00f)
				{
					
					WalkSpeed = 1;
					KNODE1->translate(Ogre::Vector3(Ogre::Math::Cos(Directiontoface),0,Ogre::Math::Sin(Directiontoface)) * WalkSpeed);
				}
				if (Stepper.getMilliseconds() >= 4500 && Directiontoface == 0.00f)
				{
					WalkSpeed = 0;
					Directiontoface = -1.60;
					KNODE1->yaw(Ogre::Degree(90));
					Stepper.reset();
				}
				if (Stepper.getMilliseconds() >= 2000 && Directiontoface == -1.60f)
				{
					
					WalkSpeed = 1;
					KNODE1->translate(Ogre::Vector3(Ogre::Math::Cos(Directiontoface),0,Ogre::Math::Sin(Directiontoface)) * WalkSpeed);
				}
				if (Stepper.getMilliseconds() >= 4500 && Directiontoface == -1.60f)
				{
					WalkSpeed = 0;
					Directiontoface = 3.20;
					KNODE1->yaw(Ogre::Degree(90));
					Stepper.reset();
				}
				if (Stepper.getMilliseconds() >= 2000 && Directiontoface == 3.20f)
				{
					
					WalkSpeed = 1;
					KNODE1->translate(Ogre::Vector3(Ogre::Math::Cos(Directiontoface),0,Ogre::Math::Sin(Directiontoface)) * WalkSpeed);
				}
				if (Stepper.getMilliseconds() >= 4450 && Directiontoface == 3.20f)
				{
					WalkSpeed = 0;
					Directiontoface = 1.60;
					KNODE1->yaw(Ogre::Degree(90));
					KNODE1->translate(Ogre::Vector3(Ogre::Math::Cos(Start.x),0,Ogre::Math::Sin(Start.z)) * WalkSpeed3);
					Stepper.reset();
				}
			
//				
			}
/////////////////////////////////////////////////////////////////////////////
//
//	Code graveyard. Only Ghosts of dead ideas rest here =).
//	Some still useful.
//

//				
//				KNODE2->translate(Ogre::Vector3(Ogre::Math::Cos(X),0,Ogre::Math::Sin(Z)) * WalkSpeed2);
//				KNODE2->translate(Ogre::Vector3(Ogre::Math::Cos(position.x),0,Ogre::Math::Sin(position.z)) * WalkSpeed2);
				//Ogre::Vector3 position = headNode->getAutoTrackLocalDirection();
				//KNODE2->translate(Ogre::Vector3(Ogre::Math::Cos(position.x),0,Ogre::Math::Sin(position.z)) * WalkSpeed2);
//				KNODE2->setAutoTracking(true,headNode,Ogre::Vector3::UNIT_Z,Ogre::Vector3::ZERO);
//				if (Stepper3.getMilliseconds() >= 250)
//					{
//						Ogre::Vector3 position2 = KNODE2->getPosition();
//						Ogre::Vector3 position = headNode->getPosition();
//						X = position.x;
//						Z = position.z;
//						X1 = position2.x;
//						Z1 = position2.z;
//						//KNODE2->translate(Ogre::Vector3(Ogre::Math::Cos(position.x),0,Ogre::Math::Sin(position.z)) * WalkSpeed2);
//						Stepper3.reset();
//					}
//				KNODE2->translate(Ogre::Vector3(Ogre::Math::Cos(X),0,Ogre::Math::Sin(Z)) * WalkSpeed2);
//						
//				if(X == X1 && Z == Z1)
//				{
//					WalkSpeed2 = 0;
//				}
//				if(X > X1 && Z > Z1)
//				{
//					WalkSpeed2 = 1;
//				}
//				if(End.getMilliseconds() >= 25000 && Move == true)
//				{
//					Move = false;
//					Stepper.reset();
//				}
				
			
		Ogre::WindowEventUtilities::messagePump();
	
	}
////////////////////////////////////////////////////////////////////////////
//
//	Shutdown operations
//
	OIS::InputManager::destroyInputSystem(lInputManager);
	lWindow->removeAllViewports();
	lScene->destroyAllCameras();
	lScene->destroyAllManualObjects();
	lScene->destroyAllEntities();
	lRootSceneNode->removeAndDestroyAllChildren();
	lMystuff.destroyResourceGroup(lNameOfResourceGroup);



	Ogre::LogManager::getSingleton().logMessage("end of the program");
	
	return 0;
}

