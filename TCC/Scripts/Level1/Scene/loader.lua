function startScript()
  print("Loading Scene from Level1")

  --criar um objeto
  local gameObject = GameObject.Instantiate()
  
  --Load Splash Image
  local component = ComponentSkybox.Instantiate(path .. "resources\\level1\\skybox\\irrlicht2_up.jpg",
                                                path .. "resources\\level1\\skybox\\irrlicht2_dn.jpg",
                                                path .. "resources\\level1\\skybox\\irrlicht2_lf.jpg",
                                                path .. "resources\\level1\\skybox\\irrlicht2_rt.jpg",
                                                path .. "resources\\level1\\skybox\\irrlicht2_ft.jpg",
                                                path .. "resources\\level1\\skybox\\irrlicht2_bk.jpg"  )
  component:AddTo(gameObject)                                              

  local component = ComponentTimer.Instantiate(10000, path .. "Scripts\\Level1\\Scene\\loader.lua","onTimeOut")
  component:AddTo(gameObject)

  local gameObject = GameObject.Instantiate()
  
  local model = ComponentModel.Instantiate( path .. "resources\\level1\\models\\plano.3DS" );
  model:AddTo(gameObject)
  
end

function onTimeOut()
  print("Bolinho!!!")
	local game = Game.GetInstance()
	game:LoadLevel("Level2");
end
