function startScript()
  print("Loading Scene from Level1")

  --criar um objeto
  local gameObject = GameObject.Instantiate("skybox")
  
  --Load Splash Image
  local component = ComponentSkybox.Instantiate(path .. "resources\\level1\\skybox\\irrlicht2_up.jpg",
                                                path .. "resources\\level1\\skybox\\irrlicht2_dn.jpg",
                                                path .. "resources\\level1\\skybox\\irrlicht2_lf.jpg",
                                                path .. "resources\\level1\\skybox\\irrlicht2_rt.jpg",
                                                path .. "resources\\level1\\skybox\\irrlicht2_ft.jpg",
                                                path .. "resources\\level1\\skybox\\irrlicht2_bk.jpg"  )
  component:AddTo(gameObject)                                              

  local gameObject = GameObject.Instantiate("plano")

  local model = ComponentModel.Instantiate( path .. "resources\\level1\\models\\plano.3DS" )
  model:AddTo(gameObject)
  
  local selector = ComponentSelector.Instantiate()
  selector:AddTo(gameObject)
  
  local interact = ComponentInteract.Instantiate(path .. "Scripts\\ObjInteraction\\door_01.lua")
  interact:AddTo(gameObject)
  
  local component = ComponentDialog.Instantiate()

  component:Say( " Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate.")
  
  component:SetPlayerImage(path .. "resources\\hero\\hero.png")
  component:SetNpcImage(path .. "resources\\hero\\hero.png")
  component:SetFont(path .. "resources\\font\\fontlucida.png")

  component:AddOption("b1", "Diga Alguma coisa!", 10, 10, 150, 25);
  component:AddImageOption("b2", path .. "resources\\common\\irrlichtlogo.jpg", 170, 10);
  component:AddOption("b3", "LEVEL 2!", 300, 10, 450, 25);

  component:AddTo(gameObject)
  
  local component = ComponentScript.Instantiate(path .. "Scripts\\Level1\\Dialog\\dialog.lua")
  component:AddTo(gameObject)
  
end
