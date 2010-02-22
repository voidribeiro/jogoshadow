function startScript()
  print("Loading Scene from Level1")

  --criar um objeto
  local gameObject = GameObject.InstPersistent("INV_GUI")
  local component = ComponentGUI.Instantiate()
  
  component:AddImageButton("inventoryButton",path .. "resources\\common\\inventory\\backpackcartoon.jpg", 707, 500)
  component:AddTo(gameObject)
  
  local component = ComponentImage.Instantiate(path .. "resources\\common\\inventory\\background.jpg")
  component:SetVisible(false);
  component:AddTo(gameObject)
  
  local component = ComponentScript.Instantiate(path .. "Scripts\\Common\\Inventory\\inventoryManager.lua")
  component:AddTo(gameObject)
  
  --local component = gameObject:GetComponentOfType("ComponentGUI")
  --print (component)
end