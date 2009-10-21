function startScript()
  print("Loading Scene from Level1")

  --criar um objeto
  local gameObject = GameObject.Instantiate()
  
  --Load Splash Image
  local component = ComponentSkybox.Instantiate(path .. "resources\\level2\\skybox\\irrlicht2_up_i.jpg",
                                                path .. "resources\\level2\\skybox\\irrlicht2_dn_i.jpg",
                                                path .. "resources\\level2\\skybox\\irrlicht2_lf_i.jpg",
                                                path .. "resources\\level2\\skybox\\irrlicht2_rt_i.jpg",
                                                path .. "resources\\level2\\skybox\\irrlicht2_ft_i.jpg",
                                                path .. "resources\\level2\\skybox\\irrlicht2_bk_i.jpg"  )
  component:AddTo(gameObject)                                              
  
  local component = ComponentTimer.Instantiate(10000, path .. "Scripts\\Level2\\Scene\\loader.lua","onTimeOut")
  component:AddTo(gameObject)

end

function onTimeOut()
  print("Bolinho!!!")
	local game = Game.GetInstance()
	game:LoadLevel("Level2");
end
