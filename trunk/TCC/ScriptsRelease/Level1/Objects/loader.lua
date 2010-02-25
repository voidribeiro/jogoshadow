function startScript()
  print("Loading Objects from Level1")
  
  createBalcao()
  createEstante()
  createDoor()
  createKey()

end

function createEstante()
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

function createBalcao()
  local balcao = GameObject.Instantiate("balcao")
  balcao:SetPosition(-50,-40,0)
   
  local component = ComponentModel.Instantiate(path .. "resources\\level1\\models\\balcao.3ds")
  component:SetTexture( path .. "resources\\level1\\textures\\textura_balcao.jpg")
  component:AddTo(balcao)
  
  local selector = ComponentSelector.Instantiate()
  selector:AddTo(balcao)
  
  local interact = ComponentInteract.Instantiate(path .. "Scripts\\Level1\\Interaction\\balcao.lua" )
  interact:AddTo(balcao) 
end

function createDoor()
  local doorHole = GameObject.Instantiate("doorHole")

  local component = ComponentModel.Instantiate(path .. "resources\\level1\\models\\doorHole.3ds")
  component:AddTo(doorHole)
  
  local selector = ComponentSelector.Instantiate()
  selector:AddTo(doorHole)
  
  local interact = ComponentInteract.Instantiate(path .. "Scripts\\Level1\\Interaction\\doorHole.lua" )
  interact:AddTo(doorHole)
  
  local door = GameObject.Instantiate("door")
  
  local component = ComponentModel.Instantiate(path .. "resources\\level1\\models\\door.3ds")
  component:AddTo(door)
  
  local selector = ComponentSelector.Instantiate()
  selector:AddTo(door)
  
  local interact = ComponentInteract.Instantiate(path .. "Scripts\\Level1\\Interaction\\door.lua" )
  interact:AddTo(door)
end

function createKey()
  local key = GameObject.Instantiate("chave")
   
  local component = ComponentModel.Instantiate(path .. "resources\\level1\\models\\key.3ds")
  component:AddTo(key)
  
  local selector = ComponentSelector.Instantiate()
  selector:AddTo(key)
  
  local interact = ComponentInteract.Instantiate(path .. "Scripts\\Level1\\Interaction\\chave.lua" )
  interact:AddTo(key) 
  
  local component = ComponentImage.Instantiate(path .. "resources\\level1\\textures\\chave.png")
  component:SetVisible(false)
  component:AddTo(key)
end