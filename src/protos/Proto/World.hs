{- This file was auto-generated from world.proto by the proto-lens-protoc program. -}
{-# LANGUAGE ScopedTypeVariables, DataKinds, TypeFamilies,
  MultiParamTypeClasses, FlexibleContexts, FlexibleInstances,
  PatternSynonyms #-}
{-# OPTIONS_GHC -fno-warn-unused-imports#-}
module Proto.World where
import qualified Prelude
import qualified Data.Int
import qualified Data.Word
import qualified Data.ProtoLens.Reexport.Data.ProtoLens
       as Data.ProtoLens
import qualified
       Data.ProtoLens.Reexport.Data.ProtoLens.Message.Enum
       as Data.ProtoLens.Message.Enum
import qualified Data.ProtoLens.Reexport.Lens.Family2
       as Lens.Family2
import qualified Data.ProtoLens.Reexport.Lens.Family2.Unchecked
       as Lens.Family2.Unchecked
import qualified Data.ProtoLens.Reexport.Data.Default.Class
       as Data.Default.Class
import qualified Data.ProtoLens.Reexport.Data.Text as Data.Text
import qualified Data.ProtoLens.Reexport.Data.Map as Data.Map
import qualified Data.ProtoLens.Reexport.Data.ByteString
       as Data.ByteString

data Object = Object{_Object'position :: Vec3,
                     _Object'rotation :: Vec3}
            deriving (Prelude.Show, Prelude.Eq)

type instance Data.ProtoLens.Field "position" Object = Vec3

instance Data.ProtoLens.HasField "position" Object Object where
        field _
          = Lens.Family2.Unchecked.lens _Object'position
              (\ x__ y__ -> x__{_Object'position = y__})

type instance Data.ProtoLens.Field "rotation" Object = Vec3

instance Data.ProtoLens.HasField "rotation" Object Object where
        field _
          = Lens.Family2.Unchecked.lens _Object'rotation
              (\ x__ y__ -> x__{_Object'rotation = y__})

instance Data.Default.Class.Default Object where
        def
          = Object{_Object'position = Data.Default.Class.def,
                   _Object'rotation = Data.Default.Class.def}

instance Data.ProtoLens.Message Object where
        descriptor
          = let position__field_descriptor
                  = Data.ProtoLens.FieldDescriptor "position"
                      (Data.ProtoLens.MessageField ::
                         Data.ProtoLens.FieldTypeDescriptor Vec3)
                      (Data.ProtoLens.PlainField Data.ProtoLens.Required position)
                rotation__field_descriptor
                  = Data.ProtoLens.FieldDescriptor "rotation"
                      (Data.ProtoLens.MessageField ::
                         Data.ProtoLens.FieldTypeDescriptor Vec3)
                      (Data.ProtoLens.PlainField Data.ProtoLens.Required rotation)
              in
              Data.ProtoLens.MessageDescriptor
                (Data.Map.fromList
                   [(Data.ProtoLens.Tag 1, position__field_descriptor),
                    (Data.ProtoLens.Tag 2, rotation__field_descriptor)])
                (Data.Map.fromList
                   [("position", position__field_descriptor),
                    ("rotation", rotation__field_descriptor)])

data Vec3 = Vec3{_Vec3'x :: Prelude.Float,
                 _Vec3'y :: Prelude.Float, _Vec3'z :: Prelude.Float}
          deriving (Prelude.Show, Prelude.Eq)

type instance Data.ProtoLens.Field "x" Vec3 = Prelude.Float

instance Data.ProtoLens.HasField "x" Vec3 Vec3 where
        field _
          = Lens.Family2.Unchecked.lens _Vec3'x
              (\ x__ y__ -> x__{_Vec3'x = y__})

type instance Data.ProtoLens.Field "y" Vec3 = Prelude.Float

instance Data.ProtoLens.HasField "y" Vec3 Vec3 where
        field _
          = Lens.Family2.Unchecked.lens _Vec3'y
              (\ x__ y__ -> x__{_Vec3'y = y__})

type instance Data.ProtoLens.Field "z" Vec3 = Prelude.Float

instance Data.ProtoLens.HasField "z" Vec3 Vec3 where
        field _
          = Lens.Family2.Unchecked.lens _Vec3'z
              (\ x__ y__ -> x__{_Vec3'z = y__})

instance Data.Default.Class.Default Vec3 where
        def
          = Vec3{_Vec3'x = Data.ProtoLens.fieldDefault,
                 _Vec3'y = Data.ProtoLens.fieldDefault,
                 _Vec3'z = Data.ProtoLens.fieldDefault}

instance Data.ProtoLens.Message Vec3 where
        descriptor
          = let x__field_descriptor
                  = Data.ProtoLens.FieldDescriptor "x"
                      (Data.ProtoLens.FloatField ::
                         Data.ProtoLens.FieldTypeDescriptor Prelude.Float)
                      (Data.ProtoLens.PlainField Data.ProtoLens.Required x)
                y__field_descriptor
                  = Data.ProtoLens.FieldDescriptor "y"
                      (Data.ProtoLens.FloatField ::
                         Data.ProtoLens.FieldTypeDescriptor Prelude.Float)
                      (Data.ProtoLens.PlainField Data.ProtoLens.Required y)
                z__field_descriptor
                  = Data.ProtoLens.FieldDescriptor "z"
                      (Data.ProtoLens.FloatField ::
                         Data.ProtoLens.FieldTypeDescriptor Prelude.Float)
                      (Data.ProtoLens.PlainField Data.ProtoLens.Required z)
              in
              Data.ProtoLens.MessageDescriptor
                (Data.Map.fromList
                   [(Data.ProtoLens.Tag 1, x__field_descriptor),
                    (Data.ProtoLens.Tag 2, y__field_descriptor),
                    (Data.ProtoLens.Tag 3, z__field_descriptor)])
                (Data.Map.fromList
                   [("x", x__field_descriptor), ("y", y__field_descriptor),
                    ("z", z__field_descriptor)])

data World = World{_World'objects :: [Object]}
           deriving (Prelude.Show, Prelude.Eq)

type instance Data.ProtoLens.Field "objects" World = [Object]

instance Data.ProtoLens.HasField "objects" World World where
        field _
          = Lens.Family2.Unchecked.lens _World'objects
              (\ x__ y__ -> x__{_World'objects = y__})

instance Data.Default.Class.Default World where
        def = World{_World'objects = []}

instance Data.ProtoLens.Message World where
        descriptor
          = let objects__field_descriptor
                  = Data.ProtoLens.FieldDescriptor "objects"
                      (Data.ProtoLens.MessageField ::
                         Data.ProtoLens.FieldTypeDescriptor Object)
                      (Data.ProtoLens.RepeatedField Data.ProtoLens.Unpacked objects)
              in
              Data.ProtoLens.MessageDescriptor
                (Data.Map.fromList
                   [(Data.ProtoLens.Tag 1, objects__field_descriptor)])
                (Data.Map.fromList [("objects", objects__field_descriptor)])

objects ::
        forall msg msg' . Data.ProtoLens.HasField "objects" msg msg' =>
          Lens.Family2.Lens msg msg' (Data.ProtoLens.Field "objects" msg)
            (Data.ProtoLens.Field "objects" msg')
objects
  = Data.ProtoLens.field
      (Data.ProtoLens.ProxySym :: Data.ProtoLens.ProxySym "objects")

position ::
         forall msg msg' . Data.ProtoLens.HasField "position" msg msg' =>
           Lens.Family2.Lens msg msg' (Data.ProtoLens.Field "position" msg)
             (Data.ProtoLens.Field "position" msg')
position
  = Data.ProtoLens.field
      (Data.ProtoLens.ProxySym :: Data.ProtoLens.ProxySym "position")

rotation ::
         forall msg msg' . Data.ProtoLens.HasField "rotation" msg msg' =>
           Lens.Family2.Lens msg msg' (Data.ProtoLens.Field "rotation" msg)
             (Data.ProtoLens.Field "rotation" msg')
rotation
  = Data.ProtoLens.field
      (Data.ProtoLens.ProxySym :: Data.ProtoLens.ProxySym "rotation")

x ::
  forall msg msg' . Data.ProtoLens.HasField "x" msg msg' =>
    Lens.Family2.Lens msg msg' (Data.ProtoLens.Field "x" msg)
      (Data.ProtoLens.Field "x" msg')
x = Data.ProtoLens.field
      (Data.ProtoLens.ProxySym :: Data.ProtoLens.ProxySym "x")

y ::
  forall msg msg' . Data.ProtoLens.HasField "y" msg msg' =>
    Lens.Family2.Lens msg msg' (Data.ProtoLens.Field "y" msg)
      (Data.ProtoLens.Field "y" msg')
y = Data.ProtoLens.field
      (Data.ProtoLens.ProxySym :: Data.ProtoLens.ProxySym "y")

z ::
  forall msg msg' . Data.ProtoLens.HasField "z" msg msg' =>
    Lens.Family2.Lens msg msg' (Data.ProtoLens.Field "z" msg)
      (Data.ProtoLens.Field "z" msg')
z = Data.ProtoLens.field
      (Data.ProtoLens.ProxySym :: Data.ProtoLens.ProxySym "z")