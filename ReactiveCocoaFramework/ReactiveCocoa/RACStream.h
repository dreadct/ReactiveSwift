//
//  RACStream.h
//  ReactiveCocoa
//
//  Created by Justin Spahr-Summers on 2012-10-31.
//  Copyright (c) 2012 GitHub, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EXTConcreteProtocol.h"

// A concrete protocol representing any stream of values. Implemented by
// RACSubscribable and RACSequence.
//
// This protocol represents a monad, upon which many stream-based operations can
// be built.
//
// When conforming to this protocol in a custom class, only `@required` methods
// need to be implemented. Default implementations will automatically be
// provided for any methods marked as `@concrete`. For more information, see
// EXTConcreteProtocol.h.
@protocol RACStream <NSObject>
@required

// Returns an empty stream.
+ (instancetype)empty;

// Lifts `value` into the stream monad.
//
// Returns a stream containing only the given value.
+ (instancetype)return:(id)value;

// Binds `block` to the values in the receiver.
//
// block - A block which accepts the values in the receiver and returns a new
//         instance of the receiver's class.
//
// Returns a new stream which represents the combined result of all applications
// of `block`.
- (instancetype)bind:(id (^)(id value))block;

// Appends the values of `stream` to the values in the receiver.
//
// stream - A stream to concatenate. This must be an instance of the same
//          concrete class as the receiver, and should not be `nil`.
//
// Returns a new stream representing the receiver followed by `stream`.
- (instancetype)concat:(id<RACStream>)stream;

@concrete

// Flattens a stream of streams.
//
// Returns a stream consisting of the concatenated streams obtained from the
// receiver.
- (instancetype)flatten;

// Maps `block` across the values in the receiver.
//
// Returns a new stream with the mapped values.
- (instancetype)map:(id (^)(id value))block;

// Returns a stream consisting of `value`, followed by the values in the
// receiver.
- (instancetype)startWith:(id)value;

// Skips the first `skipCount` values in the receiver.
//
// Returns the receiver after skipping the first `skipCount` values. If
// `skipCount` is greater than the number of values in the stream, an empty
// stream is returned.
- (instancetype)skip:(NSUInteger)skipCount;

@end
