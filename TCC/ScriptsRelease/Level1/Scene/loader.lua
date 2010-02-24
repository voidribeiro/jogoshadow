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

  local gameObject = GameObject.Instantiate("Cenario1")
  
  local model = ComponentModel.Instantiate( path .. "resources\\level1\\models\\ambient.3DS" );
  model:AddTo(gameObject)
  
  Game.CameraPosition(-70,40,-70)
  Game.CameraLookAt(0,-40,0)
end