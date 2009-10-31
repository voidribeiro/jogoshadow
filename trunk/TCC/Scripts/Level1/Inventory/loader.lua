function startScript()
  print("Loading Scene from Level1")

  --criar um objeto
  local gameObject = GameObject.Instantiate()
  local component = ComponentGUI.Instantiate()
  
  component:AddImageButton("inventoryButton",path .. "resources\\common\\inventory\\backpackcartoon.jpg", 800-121, 600-129)
  component:AddTo(gameObject)
  
  local component = ComponentImage.Instantiate(path .. "resources\\common\\inventory\\background.jpg")
  component:SetVisible(false);
  component:AddTo(gameObject)
  
  local component = ComponentScript.Instantiate(path .. "Scripts\\Level1\\Inventory\\inventoryManager.lua")
  component:AddTo(gameObject)
end