//
//  IJSVGExporter.h
//  IJSVGExample
//
//  Created by Curtis Hard on 06/01/2017.
//  Copyright © 2017 Curtis Hard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IJSVGUtils.h"

@class IJSVG;

typedef void (^IJSVGCGPathHandler)(const CGPathElement* pathElement);
typedef void (^IJSVGPathElementEnumerationBlock)(const CGPathElement* pathElement, CGPoint currentPoint);

void IJSVGExporterPathCaller(void* info, const CGPathElement* pathElement);

typedef NS_OPTIONS(NSInteger, IJSVGExporterOptions) {
    IJSVGExporterOptionNone = 1 << 0,
    IJSVGExporterOptionRemoveUselessGroups = 1 << 1,
    IJSVGExporterOptionRemoveUselessDef = 1 << 2,
    IJSVGExporterOptionMoveAttributesToGroup = 1 << 3,
    IJSVGExporterOptionCreateUseForPaths = 1 << 4,
    IJSVGExporterOptionSortAttributes = 1 << 5,
    IJSVGExporterOptionCollapseGroups = 1 << 6,
    IJSVGExporterOptionCleanupPaths = 1 << 7,
    IJSVGExporterOptionRemoveHiddenElements = 1 << 8,
    IJSVGExporterOptionScaleToSizeIfNecessary = 1 << 9,
    IJSVGExporterOptionCompressOutput = 1 << 10,
    IJSVGExporterOptionCollapseGradients = 1 << 11,
    IJSVGExporterOptionCreateClasses = 1 << 12,
    IJSVGExporterOptionRemoveWidthHeightAttributes = 1 << 13,
    IJSVGExporterOptionColorAllowRRGGBBAA = 1 << 14,
    IJSVGExporterOptionRemoveComments = 1 << 15,
    IJSVGExporterOptionCenterWithinViewBox = 1 << 16,
    IJSVGExporterOptionRemoveXMLDeclaration = 1 << 17,
    IJSVGExporterOptionConvertArcs = 1 << 18,
    IJSVGExporterOptionConvertShapesToPaths = 1 << 19,
    IJSVGExporterOptionRoundTransforms = 1 << 20,
    IJSVGExporterOptionRemoveDefaultValues = 1 << 21,
    IJSVGExporterOptionAll = IJSVGExporterOptionRemoveUselessDef | IJSVGExporterOptionRemoveUselessGroups | IJSVGExporterOptionCreateUseForPaths | IJSVGExporterOptionMoveAttributesToGroup | IJSVGExporterOptionSortAttributes | IJSVGExporterOptionCollapseGroups | IJSVGExporterOptionCleanupPaths | IJSVGExporterOptionRemoveHiddenElements | IJSVGExporterOptionScaleToSizeIfNecessary | IJSVGExporterOptionCompressOutput | IJSVGExporterOptionCollapseGradients | IJSVGExporterOptionRemoveWidthHeightAttributes | IJSVGExporterOptionColorAllowRRGGBBAA | IJSVGExporterOptionRemoveComments | IJSVGExporterOptionCenterWithinViewBox | IJSVGExporterOptionRemoveXMLDeclaration | IJSVGExporterOptionConvertArcs | IJSVGExporterOptionConvertShapesToPaths | IJSVGExporterOptionRoundTransforms | IJSVGExporterOptionRemoveDefaultValues
};

BOOL IJSVGExporterHasOption(IJSVGExporterOptions options, NSInteger option);
void IJSVGEnumerateCGPathElements(CGPathRef path, IJSVGPathElementEnumerationBlock enumBlock);
const NSArray<NSString*>* IJSVGShortCharacterArray(void);
const NSDictionary<NSString*, NSString*>* IJSVGDefaultAttributes(void);

@interface IJSVGExporter : NSObject {

@private
    IJSVG* _svg;
    CGSize _size;
    IJSVGExporterOptions _options;
    NSXMLDocument* _dom;
    NSXMLElement* _defElement;
    NSInteger _idCount;
    NSInteger _shortIdCount;
    BOOL _appliedXLink;
}

@property (nonatomic, assign) IJSVGFloatingPointOptions floatingPointOptions;
@property (nonatomic, copy) NSString* title;
@property (nonatomic, copy) NSString* desc;

- (id)initWithSVG:(IJSVG*)svg
             size:(CGSize)size
          options:(IJSVGExporterOptions)options;
- (id)initWithSVG:(IJSVG*)svg
                    size:(CGSize)size
                 options:(IJSVGExporterOptions)options
    floatingPointOptions:(IJSVGFloatingPointOptions)floatingPointOptions;

- (NSString*)SVGString;
- (NSData*)SVGData;
- (IJSVG*)SVG:(NSError**)error;

@end
