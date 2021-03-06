//
//  IJSVGStringAdditions.m
//  IconJar
//
//  Created by Curtis Hard on 07/06/2019.
//  Copyright © 2019 Curtis Hard. All rights reserved.
//

#import "IJSVGStringAdditions.h"

@implementation NSString (IJSVGAdditions)

- (NSArray<NSString*>*)ijsvg_componentsSeparatedByChars:(const char*)aChar
{
    NSMutableArray* comp = [[[NSMutableArray alloc] init] autorelease];
    NSInteger length = self.length;
    unichar* chars = (unichar*)calloc(sizeof(unichar), self.length);

    NSInteger ind = 0;
    BOOL startedString = NO;
    const char* buffer = self.UTF8String;

    for (NSInteger i = 0; i < length; i++) {
        unichar theChar = buffer[i];

        // start the buffer
        BOOL isEqualToChar = strchr(aChar, theChar) != NULL;
        if (isEqualToChar == NO) {
            startedString = YES;
            chars[ind++] = theChar;
        }

        // has started and char is the search char, or its at end
        if ((startedString == YES && isEqualToChar) || (i == (length - 1) && startedString == YES)) {
            startedString = NO;

            // append the comp
            [comp addObject:[NSString stringWithCharacters:chars length:ind]];

            // restart and realloc the memory
            ind = 0;
            chars = memset(chars, '\0', sizeof(unichar) * ind);
        }
    }
    free(chars);
    return comp;
}

- (BOOL)ijsvg_containsAlpha
{
    const char* buffer = self.UTF8String;
    char currentChar;
    while((currentChar = *buffer++) ) {
        if (isalpha(currentChar)) {
            return YES;
        }
    }
    return NO;
}

- (BOOL)ijsvg_isNumeric
{
    const char* buffer = self.UTF8String;
    char currentChar;
    while((currentChar = *buffer++) ) {
        if (!isnumber(currentChar)) {
            return NO;
        }
    }
    return YES;
}

- (NSArray*)ijsvg_componentsSplitByWhiteSpace
{
    return [self ijsvg_componentsSeparatedByChars:"\t\n\r "];
}

- (BOOL)ijsvg_isHexString
{
    const char* chars = self.UTF8String;
    char c;
    while((c = *chars++)) {
        BOOL flag = ((c == '#') ||
         (c >= '0' && c <= '9') ||
         (c >= 'a' && c <= 'f') ||
         (c >= 'A' && c <= 'F'));
        if(flag == NO) {
            return NO;
        }
    }
    return YES;
}

@end
