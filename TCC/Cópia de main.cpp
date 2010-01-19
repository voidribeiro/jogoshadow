/** IrrLicht First Time Walk **/

#include "include/irrlicht.h"
#include <iostream>

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

class MyEventReceiver : public IEventReceiver
{
	public:
	// We'll create a struct to record info on the mouse state
	struct SMouseState
	{
		core::position2di Position;
		bool LeftButtonDown;
		SMouseState() : LeftButtonDown(false) { }
	} MouseState;

	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember the mouse state
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			switch(event.MouseInput.Event)
			{
			case EMIE_LMOUSE_PRESSED_DOWN:
				MouseState.LeftButtonDown = true;
				break;

			case EMIE_LMOUSE_LEFT_UP:
				MouseState.LeftButtonDown = false;
				break;
			}
		}
		return false;
	}
	const SMouseState & GetMouseState(void) const
	{
		return MouseState;
	}


	MyEventReceiver()
	{
	}
};

int main()
{
	bool mousePress = false;

	// create event listener
	MyEventReceiver receiver;
  core::vector3df tempvec;

  tempvec.set(0,0,0);

  IrrlichtDevice *device = createDevice(video::EDT_DIRECT3D9, core::dimension2d<s32>(800, 600), 32, false, false, false, &receiver);

	if (device == 0)
		return 1; // could not create selected driver.

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

  //creates a green plane mesh
	scene::IAnimatedMesh* planeMesh = smgr->getMesh("resources/plano.3DS");
	scene::ISceneNode* planeNode = 0;

  //set the plane node
  if (planeMesh){
		planeNode = smgr->addOctTreeSceneNode(planeMesh->getMesh(0));
    planeNode->setScale(core::vector3df(2.0f,2.0f, 2.0f ));
    planeNode->setPosition(core::vector3df(0,-50,0));
  }

  //creates a triangle selector to watch the plane mesh
	scene::ITriangleSelector* selector = 0;

	if (planeNode){
		selector = smgr->createOctTreeTriangleSelector( planeMesh->getMesh(0), planeNode, 128 );
		planeNode->setTriangleSelector(selector);
	}

  //creates a first person camera
	scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 100.0f, .3f, -1, 0, 0, true, 3.f);
	camera->setPosition(core::vector3df(-100,75,-150));

	// disable mouse cursor
	device->getCursorControl()->setVisible(false);

	// add billboard
	scene::IBillboardSceneNode * bill = smgr->addBillboardSceneNode();
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
	bill->setMaterialTexture(0, driver->getTexture("resources/fireball.bmp"));
	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialFlag(video::EMF_ZBUFFER, false);
	bill->setSize(core::dimension2d<f32>(20.0f, 20.0f));

	// add 1 animated faerie.
	video::SMaterial material;
	material.setTexture(0, driver->getTexture("resources/faerie2.bmp"));
	material.Lighting = true;

	scene::IAnimatedMeshSceneNode* node = 0;
	scene::IAnimatedMesh* faerie = smgr->getMesh("resources/faerie.md2");

	if (faerie)	{
		node = smgr->addAnimatedMeshSceneNode(faerie);
		node->setPosition(core::vector3df(-30,0,-90));
		node->setMD2Animation(scene::EMAT_STAND);
		node->getMaterial(0) = material;
	}

	material.setTexture(0, 0);
	material.Lighting = false;

	// Add a light
	smgr->addLightSceneNode(0, core::vector3df(-60,300,100),
		video::SColorf(1.0f,1.0f,1.0f,1.0f),
		600.0f);

  //create a skybox
  smgr->addSkyBoxSceneNode(
                driver->getTexture("resources/irrlicht2_up.jpg"),
                driver->getTexture("resources/irrlicht2_dn.jpg"),
                driver->getTexture("resources/irrlicht2_lf.jpg"),
                driver->getTexture("resources/irrlicht2_rt.jpg"),
                driver->getTexture("resources/irrlicht2_ft.jpg"),
                driver->getTexture("resources/irrlicht2_bk.jpg"));


	/*
	For not making it to complicated, I'm doing picking inside the drawing
	loop. We take two pointers for storing the current and the last
	selected scene node and start the loop.
	*/

	scene::ISceneNode* selectedCharacter = 0;
	scene::ISceneNode* selectedSceneNode = 0;
	scene::ISceneNode* lastSelectedSceneNode = 0;

	int lastFPS = -1;

  //game loop
	while(device->run())
	if (device->isWindowActive()){
		driver->beginScene(true, true, 0);

    smgr->drawAll();

		/*
		After we've drawn the whole scene with smgr->drawAll(), we'll
		do the first picking: We want to know which triangle of the
		world we are looking at. In addition, we want the exact point
		of the quake 3 level we are looking at. For this, we create a
		3d line starting at the position of the camera and going
		through the lookAt-target of it. Then we ask the collision
		manager if this line collides with a triangle of the world
		stored in the triangle selector. If yes, we draw the 3d
		triangle and set the position of the billboard to the
		intersection point.
		*/
		selectedSceneNode =	smgr->getSceneCollisionManager()->getSceneNodeFromCameraBB(camera);

		if (lastSelectedSceneNode)
			lastSelectedSceneNode->setMaterialFlag(video::EMF_LIGHTING, true);

		if (selectedSceneNode == planeNode || selectedSceneNode == bill)
			selectedSceneNode = 0;

		if (selectedSceneNode){
			if ((!mousePress) && (receiver.GetMouseState().LeftButtonDown)){
				mousePress = true;

				if (selectedCharacter != selectedSceneNode)
					selectedCharacter = selectedSceneNode;
				else{
					node->setMD2Animation(scene::EMAT_STAND);
					selectedCharacter = 0;
				}
			}
		}

    if (selectedCharacter){
			selectedCharacter->setMaterialFlag(video::EMF_LIGHTING, false);

      if(tempvec.getDistanceFrom(node->getPosition()) < 0.1f)
          node->setMD2Animation(scene::EMAT_STAND);
    }

		lastSelectedSceneNode = selectedSceneNode;

		if (!receiver.GetMouseState().LeftButtonDown)
			mousePress = false;

		core::line3d<f32> line;
		line.start = camera->getPosition();
		line.end = line.start + (camera->getTarget() - line.start).normalize() * 1000.0f;



		core::vector3df intersection;
		core::triangle3df tri;

  if (smgr->getSceneCollisionManager()->getCollisionPoint(
			line, selector, intersection, tri))
		{
			bill->setPosition(intersection);

			driver->setTransform(video::ETS_WORLD, core::matrix4());
			driver->setMaterial(material);
			if (receiver.GetMouseState().LeftButtonDown){
				driver->draw3DTriangle(tri, video::SColor(0,255,0,0));
				if ((!mousePress) && (selectedCharacter)){

					//node->setPosition(core::vector3df(-70,0,-90));
					tempvec = tri.pointA;
					tempvec = tempvec.getInterpolated(tri.pointB,0.5);
					tempvec = tempvec.getInterpolated(tri.pointC,0.5);
					tempvec.Y += 20;
          
				  node->setMD2Animation(scene::EMAT_RUN);

          //std::cout<<tempvec.getDistanceFrom(node->getPosition());

					scene::ISceneNodeAnimator* anim =
					smgr->createFlyStraightAnimator(node->getPosition(),
					tempvec, 10*tempvec.getDistanceFrom(node->getPosition()), false);


					//Calculates the rotation

					core::vector3df requiredRotation = (tempvec-node->getAbsolutePosition());
					requiredRotation = requiredRotation.getHorizontalAngle();
					
					//Doesnt require to point down... so just rotates on Y axis
					requiredRotation.X = 0;
					requiredRotation.Z = 0;
					
					//For some reason it needs correction. Maybe the model start with a rotation
					requiredRotation.Y -= 90;
					node->setRotation(requiredRotation);


					node->addAnimator(anim);
					anim->drop();
					mousePress = true;
				}
			}
		}

    //draw everything
		driver->endScene();

		int fps = driver->getFPS();

		if (lastFPS != fps)
		{
			core::stringw str = L"First time enviorment walk - Irrlicht Engine [";
			str += driver->getName();
			str += "] FPS:";
			str += fps;

			device->setWindowCaption(str.c_str());
			lastFPS = fps;
		}
	}

	selector->drop();
	device->drop();

	return 0;
}
