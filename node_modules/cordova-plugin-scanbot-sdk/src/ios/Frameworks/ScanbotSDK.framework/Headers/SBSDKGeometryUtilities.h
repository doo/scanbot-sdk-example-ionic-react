//
//  SBSDKGeometryUtilities.h
//  doo-ios
//
//  Created by Sebastian Husche on 21.11.13.
//  Copyright (c) 2013 doo GmbH. All rights reserved.
//

#ifndef doo_ios_SBSDKGeometryUtilities_h
#define doo_ios_SBSDKGeometryUtilities_h

#import <CoreGraphics/CGGeometry.h>
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif

/**
 Converts an angle from degrees to radians.
 :nodoc:
 */
static inline CGFloat Degrees2Radians(CGFloat degrees) {
    return degrees * M_PI / 180.0f;
}

/**
 Returns the center point of a rect.
 :nodoc:
 */
static inline CGPoint RectCenterPoint(CGRect rect) {
    return CGPointMake(CGRectGetMidX(rect), CGRectGetMidY(rect));
}

/**
 Returns the size that fits into a given size by maintaining the aspect ratio.
 :nodoc:
 */
static inline CGSize SizeFitInSize(CGSize size, CGSize intoSize) {
    CGFloat xRatio = size.width / intoSize.width;
	CGFloat yRatio = size.height / intoSize.height;
	CGFloat aspectRatio = size.width / size.height;
    CGSize result;
	if (xRatio >= yRatio) {
		result.width = intoSize.width;
		result.height = floorf(result.width / aspectRatio);
	} else {
		result.height = intoSize.height;
		result.width = floorf(result.height * aspectRatio);
	}
    return result;
}

/**
 Returns the size that fills into a given size by maintaining the aspect ratio.
 :nodoc:
 */
static inline CGSize SizeFillInSize(CGSize size, CGSize intoSize) {
    CGFloat xRatio = size.width / intoSize.width;
	CGFloat yRatio = size.height / intoSize.height;
	CGFloat aspectRatio = size.width / size.height;
    CGSize result;
	if (xRatio <= yRatio) {
		result.width = intoSize.width;
		result.height = result.width / aspectRatio;
	} else {
		result.height = intoSize.height;
		result.width = result.height * aspectRatio;
	}
    return result;
}

/**
 Returns a rect with given size and origin = CGPointZero.
 :nodoc:
 */
static inline CGRect RectMakeWithSize(CGSize size) {
    return CGRectMake(0, 0, size.width, size.height);
}

/**
 Clips a rect to the boundaries of a size.
 :nodoc:
 */
static inline CGRect ClampRectToSize(CGRect rect, CGSize size) {

    rect.origin.x = MAX(0, rect.origin.x);
    rect.origin.y = MAX(0, rect.origin.y);
    
    CGFloat dX = MAX(0, CGRectGetMaxX(rect) - size.width);
    CGFloat dY = MAX(0, CGRectGetMaxY(rect) - size.height);
    
    rect.size.width -= dX;
    rect.size.height -= dY;
    
    return rect;
}

/**
 Moves a rectangle to the given center point.
 :nodoc:
 */
static inline CGRect RectWithCenter(CGRect rect, CGPoint center) {
    CGRect result = RectMakeWithSize(rect.size);
    result.origin.x = center.x - (rect.size.width * 0.5f);
    result.origin.y = center.y - (rect.size.height * 0.5f);
    return result;
}

/**
 Creates a rectangle with given size and center point.
 :nodoc:
 */
static inline CGRect RectWithSizeAndCenter(CGSize size, CGPoint center) {
    CGRect result = RectMakeWithSize(size);
    result.origin.x = center.x - (size.width * 0.5f);
    result.origin.y = center.y - (size.height * 0.5f);
    return result;
}

/**
 Centers a rectangle within the given rectangle.
 :nodoc:
 */
static inline CGRect RectCenterInRect(CGRect rect, CGRect intoRect) {
    CGPoint center = RectCenterPoint(intoRect);
    return RectWithCenter(rect, center);
}

/**
 Performs a fit-in operation of a rectangle into another rectangle. 
 :nodoc:
 */
static inline CGRect RectFitInRect(CGRect rect, CGRect intoRect) {
    CGRect result = RectMakeWithSize(SizeFitInSize(rect.size, intoRect.size));
    result = RectWithCenter(result, RectCenterPoint(intoRect));
    return result;
}

/**
 Performs a fill-in operation of a rectangle into another rectangle.
 :nodoc:
 */
static inline CGRect RectFillInRect(CGRect rect, CGRect intoRect) {
    CGRect result = RectMakeWithSize(SizeFillInSize(rect.size, intoRect.size));
    result = RectWithCenter(result, RectCenterPoint(intoRect));
    return result;
}

/**
 Non-uniform rectangle scaling.
 :nodoc:
 */
static inline CGRect RectScaled(CGRect rect, CGSize scale) {
    return CGRectMake(rect.origin.x * scale.width, 
                      rect.origin.y * scale.height, 
                      rect.size.width * scale.width, 
                      rect.size.height * scale.height);
}

/**
 Returns the vector between Point p1 and p2.
 :nodoc:
 */
static inline CGPoint VectorOfPoints(CGPoint p1, CGPoint p2) {
    CGPoint v = CGPointMake(p2.x - p1.x, p2.y - p1.y);
    return v;
}

/** 
 Returns the length of a vector.
 :nodoc:
 */
static inline double VectorLength(CGPoint vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

/**
 Returns the distance between two points, resp. the length of the vector between two points.
 :nodoc:
 */
static inline CGFloat DistanceOfPoints(CGPoint p1, CGPoint p2) {
    return VectorLength(VectorOfPoints(p1, p2));
}

/**
 Returns the normalized vector of a given vector.
 :nodoc:
 */
static inline CGPoint VectorNormalize(CGPoint vector) {
    CGFloat length = VectorLength(vector);
    if (length == 0) {
        return CGPointMake(NAN, NAN);
    }
    return CGPointMake(vector.x / length, vector.y / length);
}

/**
 Returns the product of a vector and a scalar value.
 :nodoc:
 */
static inline CGPoint VectorScalarProduct(CGPoint vector, CGFloat scalar) {
    return CGPointMake(vector.x * scalar, vector.y * scalar);
}

/** 
 Returns the dot product of two vectors.
 :nodoc:
 */
static inline double VectorDotProduct(CGPoint vector1, CGPoint vector2) {
    return (vector1.x * vector2.x) + (vector1.y * vector2.y);
}

/**
 Returns the angle between two vectors in radians.
 :nodoc:
 */
static inline CGFloat AngleOfVectors(CGPoint vector1, CGPoint vector2) {
    return acos(VectorDotProduct(VectorNormalize(vector1), VectorNormalize(vector2)));
}

/** 
 Converts an angle from radians to degrees. 
 :nodoc:
 */
static inline CGFloat Radians2Degrees(CGFloat radians) {
    return radians * 180.0f / M_PI;
}

/**
 Checks whether two lines intersect and returns the intersection point and the segment factors.
 p1: First line start point
 p2: First line end point
 p3: Second line start point
 p4: Second line end point
 intersectionPoint: Pointer to a CGPoint that will contain the intersection point when the function returns YES
 ua: Pointer to first lines segment factor. The intersection point is among the first line if 0 <= ua <= 1.
 ub: Pointer to second lines segment factor. The intersection point is among the second line if 0 <= ub <= 1.
 
 Source: http://paulbourke.net/geometry/pointlineplane/pdb.c
 :nodoc:
 */
static inline BOOL LineIntersection(CGPoint p1,
                                    CGPoint p2,
                                    CGPoint p3,
                                    CGPoint p4,
                                    CGPoint *intersectionPoint,
                                    CGFloat *ua,
                                    CGFloat *ub) {

    double mua,mub;
    double denom,numera,numerb;
    
    double epsilon = 0.00001;
    
    double x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    double y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;
    
    denom  = (y4-y3) * (x2-x1) - (x4-x3) * (y2-y1);
    numera = (x4-x3) * (y1-y3) - (y4-y3) * (x1-x3);
    numerb = (x2-x1) * (y1-y3) - (y2-y1) * (x1-x3);
    
    // Are the line coincident ?
    if (ABS(numera) < epsilon && ABS(numerb) < epsilon && ABS(denom) < epsilon) {
        if (intersectionPoint != NULL) {
            intersectionPoint->x = (x1 + x2) / 2;
            intersectionPoint->y = (y1 + y2) / 2;
        }
        return YES;
    }
    
    // Are the lines parallel ?
    if (ABS(denom) < epsilon) {
        return NO;
    }
    
    // Intersection is along the segments if mua and mub are between 0 and 1
    mua = numera / denom;
    mub = numerb / denom;

    if (intersectionPoint != NULL) {
        intersectionPoint->x = x1 + mua * (x2 - x1);
        intersectionPoint->y = y1 + mua * (y2 - y1);
    }
    
    if (ua != NULL) {
        *ua = mua;
    }
    if (ub != NULL) {
        *ub = mub;
    }
    return YES;
}


/** 
 Returns the closest distance of a point from a line. 
 point: The point.
 p1: The start point of the line.
 p2: The end point of the line.
 segmentFactor: Pointer to segment factor, 0 <= segmentFactor <= 1 if the closest point on the line is along the line segment
 :nodoc:
 */
static inline CGFloat DistanceOfPointAndLine(CGPoint point, CGPoint p1, CGPoint p2, CGFloat *segmentFactor) {
    
    CGFloat lineLength = VectorLength(VectorOfPoints(p1, p2));
    
    CGFloat dx = p2.x - p1.x;
    CGFloat dy = p2.y - p1.y;
    
    CGFloat u = ((((point.x - p1.x) * dx)
                 + ((point.y - p1.y) * dy))
                 / (lineLength * lineLength));
    
    if (segmentFactor != NULL) {
        *segmentFactor = u;
    }
    
    CGPoint intersection;
    intersection.x = p1.x + u * dx;
    intersection.y = p1.y + u * dy;
    
    return VectorLength(VectorOfPoints(point, intersection));
}

/**
 Returns the closest distance of two lines.
 p1: The start point of the first line.
 p2: The end point of the first line.
 p3: The start point of the second line.
 p4: The end point of the second line.
 :nodoc:
 */
static inline CGFloat DistanceOfLines(CGPoint p1, CGPoint p2, CGPoint p3, CGPoint p4) {
    CGFloat u12, u34;
    CGPoint intersection;
    if (LineIntersection(p1, p2, p3, p4, &intersection, &u12, &u34)) {
        BOOL inSegmentP1P2 = u12 >= 0.0f && u12 <= 1.0f;
        BOOL inSegmentP3P4 = u34 >= 0.0f && u34 <= 1.0f;
        if (inSegmentP1P2 && inSegmentP3P4) {
            return 0;
        }
        
        CGFloat minDP12P34 = MIN(DistanceOfPointAndLine(p1, p3, p4, NULL), DistanceOfPointAndLine(p2, p3, p4, NULL));
        CGFloat minDP34P12 = MIN(DistanceOfPointAndLine(p3, p1, p2, NULL), DistanceOfPointAndLine(p4, p1, p2, NULL));

        if (inSegmentP1P2) {
            return minDP34P12;
        } else if (inSegmentP3P4) {
            return minDP12P34;
        } else {
            return MIN(minDP12P34, minDP34P12);
        }
    }
    return MIN(DistanceOfPointAndLine(p3, p1, p2, NULL), DistanceOfPointAndLine(p4, p1, p2, NULL));
}



/** 
 Adds a vector to a point.
 :nodoc:
 */
static inline CGPoint PointAddVector(CGPoint point, CGPoint vector) {
    return CGPointMake(point.x + vector.x, point.y + vector.y);
}

/**
 Subtracts a vector from a point.
 :nodoc:
 */
static inline CGPoint PointSubstractVector(CGPoint point, CGPoint vector) {
    return CGPointMake(point.x - vector.x, point.y - vector.y);
}

/**
 Calculates the axis-oriented bounding box out of a bunch of points.
 :nodoc:
 */
static inline CGRect BoundingRectOfPoints(CGPoint points[], NSUInteger numPoints) {
    CGFloat minX = 0.0, minY = 0.0, maxX = 0.0, maxY = 0.0;
    for (NSUInteger i = 0; i < numPoints; i++) {
        CGPoint p = points[i];
        if (i==0) {
            minX = maxX = p.x;
            minY = maxY = p.y;
        } else {
            minX = MIN(minX, p.x);
            minY = MIN(minY, p.y);
            maxX = MAX(maxX, p.x);
            maxY = MAX(maxY, p.y);
        }
    }
    CGRect result = CGRectMake(minX, minY, maxX - minX, maxY - minY);
    return result;
}

/**
 Aligns a rectangles origin to pixels, using the main screens scale factor.
 :nodoc:
 */
static inline CGRect AlignRectToPixels(CGRect rect) {
#if TARGET_OS_IPHONE
    CGFloat scale = [UIScreen mainScreen].scale;
#else
    CGFloat scale = 1.0f;
#endif
    rect.origin.x = floorf(rect.origin.x * scale) / scale;
    rect.origin.y = floorf(rect.origin.y * scale) / scale;
    return rect;
}

/**
 :nodoc:
 */
static inline CGFloat scaleFactorToLimitSizeInSize(CGSize size, CGSize inSize) {
    if (inSize.width <= 0 || inSize.height <= 0) {
        return 1.0;
    }

    if (size.width <= inSize.width && size.height <= inSize.height) {
        return 1.0;
    }

    CGSize s = SizeFitInSize(size, inSize);
    return MAX(s.width / size.width, s.height / size.height);
}

/**
 :nodoc:
 */
static inline CGFloat scaleFactorToFitSizeInSize(CGSize size, CGSize inSize) {
    CGSize s = SizeFitInSize(size, inSize);
    return s.width / size.width;
}

/**
 :nodoc:
 */
static inline CGFloat scaleFactorToFillSizeInSize(CGSize size, CGSize inSize) {
    CGSize s = SizeFillInSize(size, inSize);
    return s.width / size.width;
}

/**
 :nodoc:
 */
static inline CGFloat scaleFactorToFitRectInRect(CGRect rect, CGRect inRect) {
    CGRect r = RectFitInRect(rect, inRect);
    return r.size.width / rect.size.width;
}

/**
 :nodoc:
 */
static inline CGFloat scaleFactorToFillRectInRect(CGRect rect, CGRect inRect) {
    CGRect r = RectFillInRect(rect, inRect);
    return r.size.width / rect.size.width;
}




/** 
 Returns a point that is being interpolated or extrapolated between start and end point.
 start: The start point.
 end: The end point.
 factor: The lerp factor. If 0 returns startPoint, if 1 returns endPoint, otherwise interpolates or extrapolates.
 :nodoc:
 */
static inline CGPoint lerpVector(CGPoint start, CGPoint end, CGFloat factor) {
    CGFloat deltaX = end.x - start.x;
    CGFloat deltaY = end.y - start.y;
    return (CGPoint){start.x + (deltaX * factor), start.y + (deltaY * factor)};
}

/** 
 This function maps a value being in the range of (minFrom, maxFrom) linearly to a value being in the range 
 (minTo, maxTo). See linear interpolation. If clamp is YES the result is clipped to the output range, otherwise result
 can be less than minTo or greater than maxTo.
 :nodoc:
 */
static inline CGFloat map(CGFloat value, CGFloat minFrom, CGFloat maxFrom, CGFloat minTo, CGFloat maxTo, BOOL clamp) {

    assert(minFrom - maxFrom != 0);
    assert(minTo - maxTo != 0);
    
    CGFloat d = (value - minFrom) / (maxFrom - minFrom);
    CGFloat mappedValue = minTo + d * (maxTo - minTo);
    
    if (clamp) {
        mappedValue = MIN(MAX(mappedValue, minTo), maxTo);
    }
    
    return mappedValue;
}


#endif
