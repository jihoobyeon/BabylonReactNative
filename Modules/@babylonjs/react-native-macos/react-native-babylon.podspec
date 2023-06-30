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

  s.libraries = 'astc-encoder',
                'etc1',
                'etc2',
                'nvtt',
                'squish',
                'pvrtc',
                'iqa',
                'edtaa3',
                'tinyexr',
                'BabylonNative',
                'bgfx',
                'bimg',
                'bx',
                'Canvas',
                'GenericCodeGen',
                'glslang',
                'Graphics',
                'jsRuntime',
                'OGLCompiler',
                'OSDependent',
                'MachineIndependent',
                'napi',
                'NativeCamera',
                'NativeCapture',
                'NativeEngine',
                'NativeInput',
                'NativeOptimizations',
                'NativeTracing',
                'SPIRV',
                'spirv-cross-core',
                'spirv-cross-glsl',
                'spirv-cross-msl',
                'tinyexr',
                'UrlLib',
                'Window',
                'XMLHttpRequest'

  s.frameworks = "MetalKit"

  s.dependency "React"
end

