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

  local gameObject = GameObject.Instantiate()
  gameObject:SetPosition(10,10,10)
  
  local model = ComponentModel.Instantiate( path .. "resources\\level2\\models\\cenario.x" );
  model:AddTo(gameObject)
end