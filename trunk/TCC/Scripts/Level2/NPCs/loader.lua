function startScript()
  print("Loading NPCs from Level2")

    --criar um objeto
  -- local skeleton = GameObject.Instantiate("skeleton")
  -- skeleton:SetPosition(50,30,50)

  -- local component = ComponentSkeleton.Instantiate(path .. "resources\\level2\\models\\skeleton\\player.x", 8 )
  -- component:AddTo(skeleton)

  local balcao = GameObject.Instantiate("balcao")
  balcao:SetPosition(-50,10,0)
   
  local component = ComponentModel.Instantiate(path .. "resources\\level2\\models\\balcao.3ds")
  component:SetTexture( path .. "resources\\level2\\textures\\textura_balcao.jpg")
  component:AddTo(balcao)


  -- local vaso = GameObject.Instantiate("vaso")

  -- local component = ComponentModel.Instantiate(path .. "resources\\level2\\models\\vaso.3ds")
  -- component:SetTexture( path .. "resources\\level2\\textures\\textura_vaso.jpg")
  -- component:AddTo(vaso)
  -- vaso:SetPosition(0,35,0)


  local estante = GameObject.Instantiate("estante")
  estante:SetPosition(-20,15,0)

  local component = ComponentModel.Instantiate(path .. "resources\\level2\\models\\estante.3ds")
  component:SetTexture( path .. "resources\\level2\\textures\\textura_estante.jpg")
  component:AddTo(estante)

end
