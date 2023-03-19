require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))

Pod::Spec.new do |s|
  s.name         = "react-native-babylon"
  s.version      = package["version"]
  s.summary      = package["description"]
  s.homepage     = package["homepage"]
  s.license      = package["license"]
  s.authors      = package["author"]

  s.platforms    = { :osx => "10.14" }
  s.source       = { :git => package["repository"]["url"], :tag => s.version }

  s.source_files = "macos/**/*.{h,m,mm}"
  s.requires_arc = true

  s.vendored_libraries = 'macos/libs/*.a'

  s.frameworks = "MetalKit"

  s.dependency "React"
end

