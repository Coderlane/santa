/// Copyright 2015 Google Inc. All rights reserved.
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///    http://www.apache.org/licenses/LICENSE-2.0
///
///    Unless required by applicable law or agreed to in writing, software
///    distributed under the License is distributed on an "AS IS" BASIS,
///    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
///    See the License for the specific language governing permissions and
///    limitations under the License.

#import "Source/common/SNTXPCUnprivilegedControlInterface.h"

///
///  Protocol implemented by santad and utilized by santactl (privileged operations)
///
@protocol SNTDaemonControlXPC <SNTUnprivilegedDaemonControlXPC>

///
///  Cache ops
///
- (void)flushCache:(void (^)(BOOL))reply;

///
///  Database ops
///
- (void)databaseRuleAddRules:(NSArray *)rules
                  cleanSlate:(BOOL)cleanSlate
                       reply:(void (^)(NSError *error))reply;
- (void)databaseEventsPending:(void (^)(NSArray *events))reply;
- (void)databaseRemoveEventsWithIDs:(NSArray *)ids;
- (void)databaseRuleForBinarySHA256:(NSString *)binarySHA256
                  certificateSHA256:(NSString *)certificateSHA256
                             teamID:(NSString *)teamID
                          signingID:(NSString *)signingID
                              reply:(void (^)(SNTRule *))reply;
- (void)retrieveAllRules:(void (^)(NSArray<SNTRule *> *rules, NSError *error))reply;

///
///  Config ops
///
- (void)setClientMode:(SNTClientMode)mode reply:(void (^)(void))reply;
- (void)setFullSyncLastSuccess:(NSDate *)date reply:(void (^)(void))reply;
- (void)setRuleSyncLastSuccess:(NSDate *)date reply:(void (^)(void))reply;
- (void)setSyncCleanRequired:(BOOL)cleanReqd reply:(void (^)(void))reply;
- (void)setAllowedPathRegex:(NSString *)pattern reply:(void (^)(void))reply;
- (void)setBlockedPathRegex:(NSString *)pattern reply:(void (^)(void))reply;
- (void)setBlockUSBMount:(BOOL)enabled reply:(void (^)(void))reply;
- (void)setRemountUSBMode:(NSArray *)remountUSBMode reply:(void (^)(void))reply;
- (void)setEnableBundles:(BOOL)bundlesEnabled reply:(void (^)(void))reply;
- (void)setEnableTransitiveRules:(BOOL)enabled reply:(void (^)(void))reply;
- (void)setEnableAllEventUpload:(BOOL)enabled reply:(void (^)(void))reply;
- (void)setDisableUnknownEventUpload:(BOOL)enabled reply:(void (^)(void))reply;
- (void)setOverrideFileAccessAction:(NSString *)action reply:(void (^)(void))reply;

///
///  Syncd Ops
///
- (void)postRuleSyncNotificationWithCustomMessage:(NSString *)message reply:(void (^)(void))reply;

@end

@interface SNTXPCControlInterface : NSObject

///
///  Returns the MachService ID for this service.
///
+ (NSString *)serviceID;

///
///  Returns the SystemExtension ID for this service.
///
+ (NSString *)systemExtensionID;

///
///  Returns an initialized NSXPCInterface for the SNTUnprivilegedDaemonControlXPC protocol.
///  Ensures any methods that accept custom classes as arguments are set-up before returning
///
+ (NSXPCInterface *)controlInterface;

///
///  Retrieve a pre-configured MOLXPCConnection for communicating with santad.
///  Connections just needs any handlers set and then can be resumed and used.
///
+ (MOLXPCConnection *)configuredConnection;

@end
