#include "OGRE/Ogre.h"
#include "OISEvents.h"
#include "OISInputManager.h"
#include "OISKeyboard.h"
//#include "Input.h"

////////////////////////////////////////////////////////////////////////////////
//																			 
//   
// 	    
//
//	Setting up ois for mouse controls. blender2ogre working!
//	Still skeleton code which fails to compile.
//	Not copying and pasteing :P.
//															
//  Todo : free look, and get mouse x,y,z and how to check whats under cursor.
// 
// same skybox issues.
//
// Grabbed a couple of "old" ogre books and been slowly working my way through. 
// 																	
//////////////////////////////////////////////////////////////////////////////


int main()
{

	
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
	lPluginNames.push_back("Plugin_BSPSceneManager");
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
	Ogre::NameValuePairList lParams;
	lParams["FSAA"] = "0"; 
	lParams["vsync"] = "true";
	lWindow = lRoot->createRenderWindow(lWindowTitle, lSizeX, lSizeY, lFullscreen, &lParams);
	
	}

	{
	Ogre::SceneManager* lScene = lRoot->createSceneManager(Ogre::ST_GENERIC, "BasicSceneManager");
	Ogre::SceneNode* lRootSceneNode = lScene->getRootSceneNode();
	Ogre::Camera* lCamera = lScene->createCamera("ViewMeCamera");
	Ogre::SceneNode* lCameraNode = lRootSceneNode->createChildSceneNode("CameraNode1");
	lCameraNode->attachObject(lCamera);
	float lViewportWidth = 0.88f;
	float lViewportHeight = 0.88f;
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
	lCamera->setPosition(Ogre::Vector3(0,400,0));
	lCamera->lookAt(Ogre::Vector3(0,20,0));
	lWindow->setActive(true);
	lWindow->setAutoUpdated(false);
	lScene->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	
	Ogre::Light* Lights = lScene->createLight("me");
	Lights->setType(Ogre::Light::LT_SPOTLIGHT);
	Lights->setDiffuseColour(1.0, 1.0, 1.0);
	Lights->setSpecularColour(1.0, 1.0, 1.0);
	Lights->setDirection(20, -2, 20);
	Lights->setPosition(20, 250.0, 20);
	Lights->setSpotlightRange(Ogre::Degree(260), Ogre::Degree(260));
	Ogre::String lNameOfResourceGroup = "First go";
	{
	Ogre::ResourceGroupManager& lMystuff = Ogre::ResourceGroupManager::getSingleton();
	lMystuff.createResourceGroup(lNameOfResourceGroup);
	Ogre::String lDirectoryToLoad = "C:/Users/Luke/Desktop/ogre/ogre.1.8.1";

	bool lIsRecursive = false;
	lMystuff.addResourceLocation(lDirectoryToLoad, "FileSystem", lNameOfResourceGroup, lIsRecursive);
	lMystuff.initialiseResourceGroup(lNameOfResourceGroup);
	lMystuff.loadResourceGroup(lNameOfResourceGroup);
		
//	Ogre::Entity* ogreHead = lScene->createEntity("Head", "ogrehead.mesh");
//	Ogre::SceneNode* headNode = lScene->getRootSceneNode()->createChildSceneNode("HeadNode");
//	headNode->attachObject(ogreHead);
//	headNode->translate(0, 0, 0);
//	ogreHead->setMaterialName("BeachStones");
//	
//	Ogre::Entity* ogreHead2 = lScene->createEntity( "Head2", "ogrehead.mesh" );
//	Ogre::SceneNode* headNode2 = lScene->getRootSceneNode()->createChildSceneNode("HeadNode2", Ogre::Vector3( 60, 0, 0 ) );
//	headNode2->attachObject(ogreHead2);
//	headNode2->translate(0, 0, 0);
//	ogreHead2->setMaterialName("GreenSkin");
//	
//	
//	Ogre::Entity* mech2 = lScene->createEntity( "mech2", "robot.mesh" );
//	Ogre::SceneNode* mechNode2 = lScene->getRootSceneNode()->createChildSceneNode("mech2", Ogre::Vector3( 0, 60, 0 ) );
//	mechNode2->attachObject(mech2);
//	mechNode2->translate(0, 0, 0);
//	mechNode2->yaw( Ogre::Degree( -90 ) );
//	mech2->setMaterialName("MRAMOR6X6");
//	
//	Ogre::Entity* athene = lScene->createEntity( "athene", "athene.mesh" );
//	Ogre::SceneNode* atheneNode = lScene->getRootSceneNode()->createChildSceneNode("athene", Ogre::Vector3( -60, 20, 0 ) );
//	atheneNode->attachObject(athene);
//	atheneNode->translate(0, 0, 0);
//	atheneNode->scale( -0.5, -0.5, -0.5 );
//	atheneNode->yaw( Ogre::Degree( -360 ) );
//	atheneNode->pitch( Ogre::Degree( -180 ) );
//	athene->setMaterialName("MRAMOR-bump");
	
	Ogre::Entity* house = lScene->createEntity("House", "house.mesh");
	Ogre::SceneNode* houseNode = lScene->getRootSceneNode()->createChildSceneNode("HouseNode",Ogre::Vector3( 130, 0, -200 ) );
	houseNode->attachObject(house);
	houseNode->translate(0, 0, 0);
	houseNode->scale( 50, 50, 50 );
	//ogreHead->setMaterialName("BeachStones");
	
	//lScene->setSkyBox(true, "clouds", 5000, true); 	// Look me up "ISSUES"
	
	
	
//	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -20);
//
//	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
//	plane, 200, 200, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
//
//	Ogre::Entity* Ground = lScene->createEntity("GroundEntity", "ground");
//	lScene->getRootSceneNode()->createChildSceneNode()->attachObject(Ground);
//
//	Ground->setMaterialName("BumpyMetal");
//	Ground->setCastShadows(false);
	

	}
	lRoot->clearEventTimes();



	while(!lWindow->isClosed())
	{
		lWindow->update(false);
		bool lVerticalSynchro = true;
		lWindow->swapBuffers(lVerticalSynchro);
		lRoot->renderOneFrame();
		Ogre::WindowEventUtilities::messagePump();
	}


	lWindow->removeAllViewports();
	lScene->destroyAllCameras();
	lScene->destroyAllManualObjects();
	lScene->destroyAllEntities();
	lRootSceneNode->removeAndDestroyAllChildren();
	
	Ogre::ResourceGroupManager& lMystuff = Ogre::ResourceGroupManager::getSingleton();
	lMystuff.destroyResourceGroup(lNameOfResourceGroup);



	Ogre::LogManager::getSingleton().logMessage("end of the program");
	}
	return 0;
}

