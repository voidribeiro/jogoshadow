function startScript()

  local player = GameObject.InstPersistent("player")
  player:SetPosition(50,30,50)

  local component = ComponentSkeleton.Instantiate(path .. "resources\\level2\\models\\skeleton\\player.x", 8 )
  component:AddTo(player)
  
  --criar um objeto
  if (Game.IsInInventory("fada") == 0) then
    local gameObject = GameObject.Instantiate("fada")
  
    --Load Splash Image
    local component = ComponentModel.Instantiate(path .. "resources\\level1\\models\\faerie.md2")
    component:SetTexture(path .. "resources\\level1\\textures\\faerie2.bmp")
    component:AddTo(gameObject)
  
    local component = ComponentImage.Instantiate(path .. "resources\\level1\\textures\\faerie2.bmp")
    component:SetVisible(false)
    component:AddTo(gameObject)

    local selector = ComponentSelector.Instantiate()
    selector:AddTo(gameObject)
  
    local interact = ComponentInteract.Instantiate(path .. "Scripts\\ObjInteraction\\door_02.lua")
    interact:AddTo(gameObject)  
  end
end
