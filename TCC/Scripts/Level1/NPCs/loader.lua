function startScript()
  --criar um objeto
  local gameObject = GameObject.Instantiate("fada")
  
  --Load Splash Image
  local component = ComponentModel.Instantiate(path .. "resources\\level1\\models\\faerie.md2")
  component:SetTexture(path .. "resources\\level1\\textures\\faerie2.bmp")
  component:AddTo(gameObject)

  local selector = ComponentSelector.Instantiate()
  selector:AddTo(gameObject)
  
  local interact = ComponentInteract.Instantiate(path .. "Scripts\\ObjInteraction\\door_02.lua")
  interact:AddTo(gameObject)  

end
