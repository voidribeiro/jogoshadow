function startScript()
  print("Loading Scene from Level2")

  --criar um objeto
  local gameObject = GameObject.Instantiate("skybox")
  
  --Load Splash Image
  local component = ComponentSkybox.Instantiate(path .. "resources\\level1\\skybox\\irrlicht2_up_i.jpg",
                                                path .. "resources\\level1\\skybox\\irrlicht2_dn_i.jpg",
                                                path .. "resources\\level1\\skybox\\irrlicht2_lf_i.jpg",
                                                path .. "resources\\level1\\skybox\\irrlicht2_rt_i.jpg",
                                                path .. "resources\\level1\\skybox\\irrlicht2_ft_i.jpg",
                                                path .. "resources\\level1\\skybox\\irrlicht2_bk_i.jpg"  )
  component:AddTo(gameObject)

  local gameObject = GameObject.Instantiate("cenario1")
  
  local model = ComponentModel.Instantiate( path .. "resources\\level1\\models\\ambient.3DS" );
  model:AddTo(gameObject)
  
  createWalkableFloor()
  
  Game.CameraPosition(-70,40,-70)
  Game.CameraLookAt(0,-40,0)
end

function createWalkableFloor()
  local gameObject = GameObject.Instantiate("chao")
  local model = ComponentModel.Instantiate( path .. "resources\\level1\\models\\chao.3DS" );
  model:AddTo(gameObject)
  
  local selector = ComponentSelector.Instantiate()
  selector:AddTo(gameObject)
  
  local interact = ComponentInteract.Instantiate(path .. "Scripts\\Level1\\Interaction\\chao.lua" )
  interact:AddTo(gameObject)
end