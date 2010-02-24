function startScript()
  print("Loading Objects from Level1")
  
  local balcao = GameObject.Instantiate("balcao")
  balcao:SetPosition(-50,-40,0)
   
  local component = ComponentModel.Instantiate(path .. "resources\\level1\\models\\balcao.3ds")
  component:SetTexture( path .. "resources\\level1\\textures\\textura_balcao.jpg")
  component:AddTo(balcao)
  
  local selector = ComponentSelector.Instantiate()
  selector:AddTo(balcao)
  
  local interact = ComponentInteract.Instantiate(path .. "Scripts\\Level1\\Interaction\\balcao.lua" )
  interact:AddTo(balcao) 


  -- local vaso = GameObject.Instantiate("vaso")

  -- local component = ComponentModel.Instantiate(path .. "resources\\level2\\models\\vaso.3ds")
  -- component:SetTexture( path .. "resources\\level2\\textures\\textura_vaso.jpg")
  -- component:AddTo(vaso)
  -- vaso:SetPosition(0,35,0)


  local estante = GameObject.Instantiate("estante")
  estante:SetPosition(-50,-40,0)

  local component = ComponentModel.Instantiate(path .. "resources\\level1\\models\\estante.3ds")
  component:SetTexture( path .. "resources\\level1\\textures\\textura_estante.jpg")
  component:AddTo(estante)
  
  local selector = ComponentSelector.Instantiate()
  selector:AddTo(estante)
  
  local interact = ComponentInteract.Instantiate(path .. "Scripts\\Level1\\Interaction\\estante.lua" )
  interact:AddTo(estante) 
end
