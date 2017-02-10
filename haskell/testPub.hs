{-# LANGUAGE OverloadedLists   #-}
{-# LANGUAGE OverloadedStrings #-}

--  Pubsub envelope publisher

-- Next steps: protobufs:
-- https://hackage.haskell.org/package/proto-lens-protoc
-- https://github.com/google/proto-lens
-- https://www.schoolofhaskell.com/user/commercial/content/monad-transformers#lift-vs-liftio

module Main where

import Control.Concurrent
import Control.Monad
import System.ZMQ4.Monadic
import Data.ProtoLens
import Proto.World

getWorld :: Float -> World
getWorld i = world
    where
        v1 = Vec3 0 0 i
        r1 = Vec3 0 0 0
        object1 = Object v1 r1
        world = World [object1]

sendMessageAndWait :: (Sender t, Message msg) => Socket z t -> msg -> Int -> ZMQ z ()
sendMessageAndWait s m i = do
    send s [] (encodeMessage m)
    liftIO $ threadDelay i

main :: IO ()
main = runZMQ $ do
    -- Prepare our publisher
    publisher <- socket Pub
    connect publisher "tcp://127.0.0.1:5555"

    -- forever $ do
    forM_ [1,2] $ \i -> sendMessageAndWait publisher (getWorld 0) 1000000
