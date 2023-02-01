
export interface DocumentScannerAccessibilityConfiguration {
    /**
     * Text, that is used as an accessibility label for the flash button.
     */
    flashButtonAccessibilityLabel: string;
    /**
     * Text, that is used as an accessibility hint for the flash button.
     */
    flashButtonAccessibilityHint: string;
    /**
     * Text, that is used as an accessibility label for the multi-page button.
     */
    multiPageButtonAccessibilityLabel: string;
    /**
     * Text, that is used as an accessibility hint for the multi-page button.
     */
    multiPageButtonAccessibilityHint: string;
    /**
     * Text, that is used as an accessibility label for the auto-snapping button.
     */
    autoSnappingButtonAccessibilityLabel: string;
    /**
     * Text, that is used as an accessibility hint for the auto-snapping button.
     */
    autoSnappingButtonAccessibilityHint: string;
    /**
     * Text, that is used as an accessibility label for the cancel button.
     */
    cancelButtonAccessibilityLabel: string;
    /**
     * Text, that is used as an accessibility hint for the cancel button.
     */
    cancelButtonAccessibilityHint: string;
    /**
     * Text, that is used as an accessibility label for the page-amount button.
     */
    pageCounterButtonAccessibilityLabel: string;
    /**
     * Text, that is used as an accessibility hint for the page-amount button.
     */

    pageCounterAccessibilityHint: string;
    /**
     * Text, that is used as an accessibility label for the shutter button.
     */
    shutterButtonAccessibilityLabel: string;
    /**
     * Text, that is used as an accessibility hint for the shutter button.
     */
    shutterButtonAccessibilityHint: string;
}

export interface DocumentScannerConfiguration {
    /**
     * The minimum score in percent (0 - 100) of the perspective distortion to accept a detected document.
     * Default is 75.0.
     */
    acceptedAngleScore?: number;
    /**
     * The minimum document width or height in percent (0 - 100) of the screen size to accept a detected document.
     * Default is 80.0.
     */
    acceptedSizeScore?: number;
    /**
     * Controls whether the auto-snapping toggle button is hidden or not.
     */
    autoSnappingButtonHidden?: boolean;
    /**
     * Title of the auto-snapping toggle button.
     */
    autoSnappingButtonTitle?: string;
    /**
     * When auto-snapping is enabled the document scanner will take a photo automatically
     * when a document is detected, conditions are good and the auto-snapping time-out elapses. In this
     * mode the user can still tap the shutter button to snap a document.
     */
    autoSnappingEnabled?: boolean;
    /**
     * Controls the auto-snapping speed. Sensitivity must be within the 0..1 range.
     * A value of 1.0 triggers automatic capturing immediately, a value of 0.0 delays the automatic by 3 seconds.
     * The default value is 0.66 (1 second).
     */
    autoSnappingSensitivity?: number;
    /**
     * The radius to use when drawing rounded corners of the polygon. Default is 8.0.
     */
    polygonCornerRadius?: number;
    /**
     * Stroke color of polygon auto snap progress animation. Default is green. Can't be null.
     */
    polygonAutoSnapProgressColor?: string;
    /**
     * Line width of polygon auto snap progress animation. Default is 5.0.
     */
    polygonAutoSnapProgressLineWidth?: number;
    /**
     * Whether polygon auto snap progress animation is enabled or no. Default is true.
     */
    polygonAutoSnapProgressEnabled?: boolean;
    /**
     * The background color of the bottom shutter-bar.
     */
    bottomBarBackgroundColor?: string;
    /**
     * The color of the title of all buttons in the bottom shutter-bar (Cancel button, etc.),
     * as well as the camera permission prompt button.
     */
    bottomBarButtonsColor?: string;
    /**
     * The color of the camera background (relevant only when the camera preview mode is CameraPreviewMode.FIT_IN).
     */
    cameraBackgroundColor?: string;
    /**
     * Preview mode of the camera: Fit-In or Fill-In.
     * Optional, default is Fit-In.
     */
    cameraPreviewMode?: CameraPreviewMode;
    /**
     * Title of the cancel button.
     */
    cancelButtonTitle?: string;
    /**
     * Title of the button that opens the screen where the user can allow
     * the usage of the camera by the app.
     */
    enableCameraButtonTitle?: string;
    /**
     * Text that will be displayed when the app
     * is not allowed to use the camera, prompting the user
     * to enable the usage of the camera.
     */
    enableCameraExplanationText?: string;
    /**
     * Controls whether the flash toggle button is hidden or not.
     */
    flashButtonHidden?: boolean;
    /**
     * Title of the flash toggle button.
     */
    flashButtonTitle?: string;
    /**
     * Controls whether the flash should be initially enabled.
     * The default value is FALSE.
     */
    flashEnabled?: boolean;
    /**
     * Sets whether to ignore the net.doo.snap.lib.detector.DetectionResult.OK_BUT_BAD_ASPECT_RATIO detection status.
     * By default BadAspectRatio is not ignored.
     */
    ignoreBadAspectRatio?: boolean;
    /**
     * The image scaling factor. The factor must be within the 0..1 range.
     * A factor of 1 means that the resulting images retain their original size.
     * When the factor is less than 1, resulting images will be made smaller by that factor.
     * By default the scale is 1.
     */
    imageScale?: number;
    /**
     * Controls whether the multi-page toggle button is hidden or not.
     */
    multiPageButtonHidden?: boolean;
    /**
     * Title of the multi-page mode toggle button.
     */
    multiPageButtonTitle?: string;
    /**
     * Controls multi-page mode. When enabled, the user can take multiple document photos before
     * closing the screen by tapping the page counter button. When disabled, the screen will be
     * closed immediately after the first document photo is made.
     * The default value is FALSE.
     */
    multiPageEnabled?: boolean;
    /**
     * Orientation lock mode of the UI, the camera preview, and the output images.
     * By default the orientation is not locked.
     */
    interfaceOrientation?: UIInterfaceOrientationMask;
    /**
     * Title suffix of the button that finishes the document scanning when multi-page scanning is enabled.
     * The button's title has the format "# Pages", where # shows the number of images captured up to now and the
     * suffix "Pages" is set using this method.
     */
    pageCounterButtonTitle?: string;
    /**
     * The background color of the detected document outline when the document's angle, size or aspect ratio
     * is not yet sufficiently good.
     * (All net.doo.snap.lib.detector.DetectionResult with OK_BUT_XXX).
     */
    polygonBackgroundColor?: string;
    /**
     * The background color of the detected document outline when we are ready to snap net.doo.snap.lib.detector.DetectionResult.OK.
     */
    polygonBackgroundColorOK?: string;
    /**
     * The color of the detected document outline when the document's angle, size or aspect ratio
     * is not yet sufficiently good.
     * (All detection statuses in net.doo.snap.lib.detector.DetectionResult that have the OK_BUT_XXX prefix).
     */
    polygonColor?: string;
    /**
     * The color of the detected document outline when we are ready to snap net.doo.snap.lib.detector.DetectionResult.OK.
     */
    polygonColorOK?: string;
    /**
     * Width of the detected document outline.
     */
    polygonLineWidth?: number;
    /**
     * The foreground color of the shutter button in auto-snapping mode.
     */
    shutterButtonAutoInnerColor?: string;
    /**
     * The background color of the shutter button in auto-snapping mode.
     */
    shutterButtonAutoOuterColor?: string;
    shutterButtonIndicatorColor?: string;
    /**
     * The foreground color of the shutter button in manual mode.
     */
    shutterButtonManualInnerColor?: string;
    /**
     * The background color of the shutter button in manual mode.
     */
    shutterButtonManualOuterColor?: string;
    /**
     * Text hint that will be shown when the current detection status is net.doo.snap.lib.detector.DetectionResult.OK_BUT_BAD_ANGLES
     */
    textHintBadAngles?: string;
    /**
     * Text hint that will be shown when the current detection status is net.doo.snap.lib.detector.DetectionResult.OK_BUT_BAD_ASPECT_RATIO
     */
    textHintBadAspectRatio?: string;
    /**
     * Text hint that will be shown when the current detection status is net.doo.snap.lib.detector.DetectionResult.ERROR_NOTHING_DETECTED
     */
    textHintNothingDetected?: string;
    /**
     * Text hint that will be shown when the current detection status is net.doo.snap.lib.detector.DetectionResult.OK
     */
    textHintOK?: string;
    /**
     * Text hint that will be shown when the current detection status is net.doo.snap.lib.detector.DetectionResult.ERROR_TOO_DARK
     */
    textHintTooDark?: string;
    /**
     * Text hint that will be shown when the current detection status is net.doo.snap.lib.detector.DetectionResult.ERROR_TOO_NOISY
     */
    textHintTooNoisy?: string;
    /**
     * Text hint that will be shown when the current detection status is net.doo.snap.lib.detector.DetectionResult.OK_BUT_TOO_SMALL
     */
    textHintTooSmall?: string;
    /**
     * The background color of the top toolbar.
     */
    topBarBackgroundColor?: string;
    /**
     * The color of all active toggle buttons in the toolbar.
     */
    topBarButtonsActiveColor?: string;
    /**
     * The color of all inactive toggle buttons in the toolbar.
     */
    topBarButtonsInactiveColor?: string;
    /**
     * The background color of the user guidance hints.
     */
    userGuidanceBackgroundColor?: string;
    /**
     * The text color of the user guidance hints.
     */
    userGuidanceTextColor?: string;
    /**
     * Limits the maximum size of the document image. If width or height are zero, this property is effectively ignored.
     */
    documentImageSizeLimit?: Size;
    /**
     * Hides the shutter button if set to TRUE. Shows it otherwise. Defaults to FALSE.
     * If set to TRUE, auto-snapping is enabled and the property autoSnappingEnabled of the behaviour configuration will
     * have no effect.
     * Also the auto-snapping button will be hidden.
     */
    shutterButtonHidden?: boolean;
    /**
     * The text being displayed on the user-guidance label, when the scanners energy saver is activated.
     * iOS only.
     */
    textHintEnergySavingActive?: string;
    /**
     * Maximum number of pages to scan. Ignored when set to null, or when `multiPageEnabled` is FALSE. Default value is null.
     */
    maxNumberOfPages?: number;
    /**
     * Controls whether buttons should use all capitals style, as defined by the Android Material Design. Defaults to TRUE.
     * Android only.
     */
    useButtonsAllCaps?: boolean;
    /**
     * Allows you to customize the accessibility configuration for the Document Scanner UI
     */
    accessibilityConfiguration?: DocumentScannerAccessibilityConfiguration;
    /**
     * Set whether camera should force maximum possible size of snapped picture
     * or use maximum size that available with the same aspect ratio as preview
     * default is false
     * Android only
     */
    forceMaxSnappingSize?: boolean;
}

export interface GenericDocumentField {
    text?: string;
    confidence?: number;
}

export type GenericDocumentFields =
    DeDriverLicenseResult
    | DePassportResult
    | DeIdCardResult
    ;

export type GenericDocumentType =
    'DeDriverLicense'
    | 'DePassport'
    | 'DeIdCard'
    ;

export type CheckRecognizerResultStatus =
    'SUCCESS'
    | 'CANCELED'
    | 'FAIL';

export type CheckType =
    'USACheck'
    | 'FRACheck'
    | 'KWTCheck'
    | 'AUSCheck'
    | 'INDCheck'
    | 'UnknownCheck'
    ;

export type CheckRecognizerFieldValidationStatus =
    'Invalid'
    | 'Valid'
    ;

export type CheckRecognizerFields =
    USACheckResult
    | FRACheckResult
    | KWTCheckResult
    | AUSCheckResult
    | INDCheckResult
    | UnknownCheckResult
    ;

export interface CheckRecognizerField {
    value?: GenericDocumentField;
    validationStatus?: CheckRecognizerFieldValidationStatus;
}

interface CheckResultCommon {
    fontType?: CheckRecognizerField;
    rawString?: CheckRecognizerField;
}

export interface USACheckResult extends CheckResultCommon {
    accountNumber?: CheckRecognizerField;
    auxiliaryOnUs?: CheckRecognizerField;
    transitNumber?: CheckRecognizerField;
}

export interface FRACheckResult extends CheckResultCommon {
    accountNumber?: CheckRecognizerField;
    chequeNumber?: CheckRecognizerField;
    routingNumber?: CheckRecognizerField;
}

export interface KWTCheckResult extends CheckResultCommon {
    accountNumber?: CheckRecognizerField;
    chequeNumber?: CheckRecognizerField;
    sortCode?: CheckRecognizerField;
}

export interface AUSCheckResult extends CheckResultCommon {
    accountNumber?: CheckRecognizerField;
    auxDomestic?: CheckRecognizerField;
    bsb?: CheckRecognizerField;
    extraAuxDomestic?: CheckRecognizerField;
    transactionCode?: CheckRecognizerField;
}

export interface INDCheckResult extends CheckResultCommon {
    accountNumber?: CheckRecognizerField;
    serialNumber?: CheckRecognizerField;
    sortNumber?: CheckRecognizerField;
    transactionCode?: CheckRecognizerField;
}

export interface UnknownCheckResult extends CheckResultCommon { }

export interface CheckRecognizerConfiguration {
    /**
     * An optional array of check types that act as a detection filter.
     * By default all supported document formats will be detected.
     */
    acceptedCheckStandards?: CheckType[];
    /**
    * The preferred camera module (default: BACK)
    */
    cameraModule?: CameraModule;
    /**
    * Background color of the detection overlay.
    */
    cameraOverlayColor?: string;
    /**
     * Title of the cancel button.
     */
    cancelButtonTitle?: string;
    /**
     * Set high-resolution Check image capturing.
     */
    captureHighResolutionImage?: boolean;
    /**
     * Title of the button that opens the screen where the user can allow
     * the usage of the camera by the app.
     */
    enableCameraButtonTitle?: string;
    /**
     * Text that will be displayed when the app
     * is not allowed to use the camera, prompting the user
     * to enable the usage of the camera.
     */
    enableCameraExplanationText?: string;
    /**
     * Aspect ratio of finder frame (width \ height), which is used to build actual finder frame.
     * Default is 1 - it is a square frame, which is good for QR capturing.
     */
    finderAspectRatio?: FinderAspectRatio;
    /**
     * Foreground color of the detection overlay.
     */
    finderLineColor?: string;
    /**
     * Width of finder frame border. Default is 2.
     */
    finderLineWidth?: number;
    /**
     * Controls whether the flash should be initially enabled.
     * The default value is FALSE.
     */
    flashEnabled?: boolean;
    /**
     * Orientation lock mode of the UI, the camera preview, and the output images.
     * By default the orientation is not locked.
     */
    interfaceOrientation?: UIInterfaceOrientationMask;
    /**
     * Background color of the top bar.
     */
    topBarBackgroundColor?: string;
    /**
     * Foreground color of the top bar buttons on the scanning screen.
     */
    topBarButtonsColor?: string;
    /**
     * Foreground color of the flash button when flash is off.
     */
    topBarButtonsInactiveColor?: string;
    /**
     * Controls whether buttons should use all capitals style, as defined by the Android Material Design. Defaults to TRUE.
     * Android only.
     */
    useButtonsAllCaps?: boolean;
    /**
     * The background color of the user guidance hints.
     */
    userGuidanceBackgroundColor?: string;
    /**
     * The text color of the user guidance hints.
     */
    userGuidanceTextColor?: string;
}

export interface CheckRecognizerResult {
    checkType?: CheckType;
    imageUri?: string;
    status?: CheckRecognizerResultStatus;
    fields?: CheckRecognizerFields;
}

export class GenericDocumentRecognizerResult {
    documentType: GenericDocumentType;
    status: Status;
    fields: GenericDocumentFields;
}

export interface DeDriverLicenseResult {
    birthDate?: GenericDocumentField;
    birthplace?: GenericDocumentField;
    expiryDate?: GenericDocumentField;
    givenNames?: GenericDocumentField;
    id?: GenericDocumentField;
    issueDate?: GenericDocumentField;
    issuingAuthority?: GenericDocumentField;
    licenseCategories?: GenericDocumentField;
    photoImageUri?: string;
    signatureImageUri?: string;
    surname?: GenericDocumentField;
    restrictions?: GenericDocumentField;
    categories?: DriverLicenseCategories;
}

export interface DriverLicenseCategories {
    a?: DriverLicenseCategory;
    a1?: DriverLicenseCategory;
    a2?: DriverLicenseCategory;
    b?: DriverLicenseCategory;
    b1?: DriverLicenseCategory;
    be?: DriverLicenseCategory;
    c?: DriverLicenseCategory;
    c1?: DriverLicenseCategory;
    c1e?: DriverLicenseCategory;
    ce?: DriverLicenseCategory;
    d?: DriverLicenseCategory;
    d1?: DriverLicenseCategory;
    d1e?: DriverLicenseCategory;
    de?: DriverLicenseCategory;
    l?: DriverLicenseCategory;
    m?: DriverLicenseCategory;
    t?: DriverLicenseCategory;
}

export interface DriverLicenseCategory {
    restrictions?: GenericDocumentField;
    validFrom?: GenericDocumentField;
    validUntil?: GenericDocumentField;
}

export interface DePassportResult {
    birthDate?: GenericDocumentField;
    birthplace?: GenericDocumentField;
    countryCode?: GenericDocumentField;
    expiryDate?: GenericDocumentField;
    gender?: GenericDocumentField;
    givenNames?: GenericDocumentField;
    id?: GenericDocumentField;
    issueDate?: GenericDocumentField;
    issuingAuthority?: GenericDocumentField;
    maidenName?: GenericDocumentField;
    nationality?: GenericDocumentField;
    passportType?: GenericDocumentField;
    photoImageUri?: string;
    rawMrz?: GenericDocumentField;
    signatureImageUri?: string;
    surname?: GenericDocumentField;
    mrz?: MrzDocumentResult;
}

export interface MrzDocumentResult {
    birthDate?: GenericDocumentField;
    checkDigits?: GenericDocumentField[];
    documentNumber?: GenericDocumentField;
    expiryDate?: GenericDocumentField;
    gender?: GenericDocumentField;
    givenNames?: GenericDocumentField;
    issuingAuthority?: GenericDocumentField;
    nationality?: GenericDocumentField;
    optional1?: GenericDocumentField;
    optional2?: GenericDocumentField;
    surname?: GenericDocumentField;
    travelDocType?: GenericDocumentField;
    travelDocTypeVariant?: GenericDocumentField;
}

export interface DeIdCardResult {
    birthDate?: GenericDocumentField;
    birthplace?: GenericDocumentField;
    expiryDate?: GenericDocumentField;
    givenNames?: GenericDocumentField;
    id?: GenericDocumentField;
    maidenName?: GenericDocumentField;
    nationality?: GenericDocumentField;
    pin?: GenericDocumentField;
    photoImageUri?: string;
    signatureImageUri?: string;
    surname?: GenericDocumentField;
    address?: GenericDocumentField;
    eyeColor?: GenericDocumentField;
    height?: GenericDocumentField;
    issueDate?: GenericDocumentField;
    issuingAuthority?: GenericDocumentField;
    pseudonym?: GenericDocumentField;
    rawMrz?: GenericDocumentField;
}

export interface GenericDocumentRecognizerConfiguration {
    /**
     * Accepted document types. All other document types will be ignored.
     * All by default - DeIdFront, DeIdBack, DePassport, DeDriverLicenseFront, and DeDriverLicenseBack
     */
    acceptedDocumentTypes?: RootDocumentType[]
    /**
    * Background color of the detection overlay.
    */
    cameraOverlayColor?: string;
    /**
     * Whether the cancel button is hidden or not. (iOS only)
     */
    cancelButtonHidden?: boolean;
    /**
     * String being displayed on the cancel button.
     */
    cancelButtonTitle?: string;
    /**
     * String being displayed on the clear button.
     */
    clearButtonTitle?: string;
    /**
     * String that shows average confidence value of scanned card. Use %d as number formatting symbol.
     */
    confidenceValue?: string;
    /**
     * Foreground color of the top bar buttons on the details screen.
     */
    detailsActionColor?: string;
    /**
     * Background color of the details screen.
     */
    detailsBackgroundColor?: string;
    /**
     * Text color in the details list. Also affects image background and separator.
     */
    detailsPrimaryColor?: string;
    /**
     * Foreground color of the detection overlay.
     */
    finderLineColor?: string;
    /**
     * Width of finder frame border. Default is 2.
     */
    finderLineWidth?: number;
    /**
     * Whether the torch light is toggled on or off.
     */
    flashEnabled?: boolean;
    /**
     * A title to show image content.
     */
    imageTitle?: string;
    /**
     * String that notifies that nothing was scanned yet.
     */
    noDataTitle?: string;
    /**
     * String that asks user to scan back side of a card.
     */
    scanBackSideTitle?: string;
    /**
     * String that asks user to scan front side of a card.
     */
    scanFrontSideTitle?: string;
    /**
     * String that notifies that both sides of card are scanned.
     */
    scannedEverythingTitle?: string;
    /**
     * Defines, if photo image should be stored in internal storage on disk.
     */
    shouldSavePhotoImageInStorage?: boolean;
    /**
     * Defines, if signature image should be stored in internal storage on disk.
     */
    shouldSaveSignatureImageInStorage?: boolean;
    /**
     * String that asks user to start scanning a card.
     */
    startScanningTitle?: string;
    /**
     * String being displayed on the submit button.
     */
    viewResultsButtonTitle?: string;
    /**
     * Color of tip background on scanning screen.
     */
    tipBackgroundColor?: string;
    /**
     * Color of tip text on scanning screen.
     */
    tipTextColor?: string;
    /**
     * Background color of the top bar.
     */
    topBarBackgroundColor?: string;
    /**
     * Foreground color of the top bar buttons on the scanning screen.
     */
    topBarButtonsColor?: string;
    /**
     * Foreground color of the flash button when flash is off.
     */
    topBarButtonsInactiveColor?: string;
    /**
     * Controls whether buttons should use all capitals style, as defined by the Android Material Design. Defaults to TRUE.
     * Android only.
     */
    useButtonsAllCaps?: boolean;
    /**
     * The accepted minimal sharpness score. Images with a score less than that will
     * be rejected with blurry status.
     *
     * 0 - any image will be accepted.
     * 80 - a good compromise; the recommended setting.
     * 100 - only very sharp images will be accepted.
     *
     * The default value is 80.
     */
    sharpnessAcceptanceFactor?: number;
    /**
     * Orientation lock mode of the UI, the camera preview, and the output images.
     * By default the orientation is not locked.
     */
    interfaceOrientation?: UIInterfaceOrientationMask;
    /**
     * Text that will be displayed when the app
     * is not allowed to use the camera, prompting the user
     * to enable the usage of the camera.
     */
    enableCameraExplanationText?: string;
    /**
     * Title of the button that opens the screen where the user can allow
     * the usage of the camera by the app.
     */
    enableCameraButtonTitle?: string;
    /**
     * Text color of the fields count label.
     */
    fieldsCountTextColor?: string;
    /**
     * String used for displaying amount of detected fields. Use %d for number formatting symbol.
     */
    fieldsCountText?: string;
    /**
     * Color of confidence value label background in details screen, when the field confidence level is high.
     */
    fieldConfidenceHighColor?: string;
    /**
     * Color of confidence value label background  in details screen, when the field confidence level is moderate.
     */
    fieldConfidenceModerateColor?: string;
    /**
     * Color of confidence value label background  in details screen, when the field confidence level is low.
     */
    fieldConfidenceLowColor?: string;
    /**
     * Color of confidence value label text in details.
     */
    fieldConfidenceTextColor?: string;
    /**
     * Configuration of document fields shown in details screen
     */
    detailsFieldConfiguration?: GenericDocumentFieldConfiguration;
}

export interface GenericDocumentFieldConfiguration {
    /**
     * A title for IdCardBack in details screen.
     */
    deIdCardBackDocumentTitle?: string;
    /**
     * A title for IdCardFront in details screen.
     */
    deIdCardFrontDocumentTitle?: string;
    /**
     * A title for Passport in details screen.
     */
    dePassportDocumentTitle?: string;
    /**
     * A title for DriverLicenseBack in details screen.
     */
    deDriverLicenseBackDocumentTitle?: string;
    /**
     * A title for DriverLicenseFront in details screen.
     */
    deDriverLicenseFrontDocumentTitle?: string;
    /**
     * A title for address field in details screen.
     */
    fieldAddressTitle?: string;
    /**
     * A title for birth date field in details screen.
     */
    fieldBirthDateTitle?: string;
    /**
     * A title for birth place field in details screen.
     */
    fieldBirthPlaceTitle?: string;
    /**
     * A title for country code field in details screen.
     */
    fieldCountryCodeTitle?: string;
    /**
     * A title for expiry date field in details screen.
     */
    fieldExpiryDateTitle?: string;
    /**
     * A title for eye color field in details screen.
     */
    fieldEyeColorTitle?: string;
    /**
     * A title for gender field in details screen.
     */
    fieldGenderTitle?: string;
    /**
     * A title for given names field in details screen.
     */
    fieldGivenNamesTitle?: string;
    /**
     * A title for height field in details screen.
     */
    fieldHeightTitle?: string;
    /**
     * A title for id field in details screen.
     */
    fieldIdTitle?: string;
    /**
     * A title for issuing date field in details screen.
     */
    fieldIssueDateTitle?: string;
    /**
     * A title for issuing authority  field in details screen.
     */
    fieldIssuingAuthorityTitle?: string;
    /**
     * A title for maiden name field in details screen.
     */
    fieldMaidenNameTitle?: string;
    /**
     * A title for machine readable zone field in details screen.
     */
    fieldRawMrzTitle?: string;
    /**
     * A title for nationality field in details screen.
     */
    fieldNationalityTitle?: string;
    /**
     * A title for passport type field in details screen.
     */
    fieldPassportTypeTitle?: string;
    /**
     * A title for photo field in details screen.
     */
    fieldPhotoTitle?: string;
    /**
     * A title for PIN field in details screen.
     */
    fieldPinTitle?: string;
    /**
     * A title for pseudonym field in details screen.
     */
    fieldPseudonymTitle?: string;
    /**
     * A title for signature field in details screen.
     */
    fieldSignatureTitle?: string;
    /**
     * A title for surname field in details screen.
     */
    fieldSurnameTitle?: string;
    /**
     * A title for restrictions for the driver's license in details screen.
     */
    fieldRestrictionsTitle?: string;
    /**
     * A title for driver's license categories in details screen.
     */
    fieldLicenseCategoriesTitle?: string;
}

export interface CroppingScreenAccessibilityConfiguration {
    /**
     * Text, that is used as an accessibility label for the cancel button.
     */
    cancelButtonAccessibilityLabel: string;
    /**
     * Text, that is used as an accessibility hint for the cancel button.
     */
    cancelButtonAccessibilityHint: string;
    /**
     * Text, that is used as an accessibility label for the done button.
     */
    doneButtonAccessibilityLabel: string;
    /**
     * Text, that is used as an accessibility hint for the done button.
     */
    doneButtonAccessibilityHint: string;
    /**
     * Text, that is used as an accessibility label for the detect button.
     */
    detectButtonAccessibilityLabel: string;
    /**
     * Text, that is used as an accessibility hint for the detect button.
     */
    detectButtonAccessibilityHint: string;
    /**
     * Text, that is used as an accessibility label for the reset button.
     */
    resetButtonAccessibilityLabel: string;
    /**
     * Text, that is used as an accessibility hint for the reset button.
     */
    resetButtonAccessibilityHint: string;
    /**
     * Text, that is used as an accessibility label for the rotate button.
     */
    rotateButtonAccessibilityLabel: string;
    /**
     * Text, that is used as an accessibility hint for the rotate button.
     */
    rotateButtonAccessibilityHint: string;
}

export interface CroppingScreenConfiguration {
    /**
     * String being displayed as a hint. Empty by default.
     */
    hintTitle?: string;
    /**
     * Text color of the hint title.
     */
    hintTitleColor?: string;
    /**
     * Background color of the main screen.
     */
    backgroundColor?: string;
    /**
     * Background color of the bottom toolbar.
     */
    bottomBarBackgroundColor?: string;
    /**
     * Color of the titles of all buttons in the bottom toolbar (Rotate button).
     */
    bottomBarButtonsColor?: string;
    /**
     * Title of the cancel button.
     */
    cancelButtonTitle?: string;
    /**
     * Title of the Done button.
     */
    doneButtonTitle?: string;
    /**
     * Default color of the cropping outline.
     */
    polygonColor?: string;
    /**
     * Outline color of magnetically snapped edges.
     */
    polygonColorMagnetic?: string;
    /**
     * Width of the cropping outline.
     */
    polygonLineWidth?: number;
    /**
     * Title of the Rotate button.
     */
    rotateButtonTitle?: string;
    /**
     * Background color of the top toolbar.
     */
    topBarBackgroundColor?: string;
    /**
     * Color of the titles of all buttons in the top toolbar (Cancel and Done buttons).
     */
    topBarButtonsColor?: string;
    /**
     * Title in the top bar (iOS only).
     */
    topBarTitle?: string;
    /**
     * Color of the title in the top bar (iOS only).
     */
    titleColor?: string;
    /**
     * Title of the Detect button.
     */
    detectButtonTitle?: string;
    /**
     * Title of the Reset button.
     */
    resetButtonTitle?: string;
    /**
     * Controls whether the Rotate button is hidden or not.
     */
    rotateButtonHidden?: boolean;
    /**
     * Controls whether the Detect/Reset button is hidden or not.
     */
    detectResetButtonHidden?: boolean;
    /**
     * UI orientation lock mode: PORTRAIT, LANDSCAPE, etc.
     * By default the UI is not locked.
     */
    interfaceOrientation?: UIInterfaceOrientationMask;
    /**
     * Controls whether buttons should use all capitals style, as defined by the Android Material Design. Defaults to TRUE.
     * Android only.
     */
    useButtonsAllCaps?: boolean;
    /**
     * Allows you to customize the accessibility configuration for the Cropping Screen UI.
     */
    accessibilityConfiguration?: CroppingScreenAccessibilityConfiguration;
    /** 
     * Defines if the top and bottom buttons are swapped. Default is false.
    */
    topAndBottomButtonsSwapped?: boolean;
}

export interface MrzScannerConfiguration {
    /**
     * Background color outside of the finder window.
     */
    cameraOverlayColor?: string;
    /**
     * Title of the cancel button.
     */
    cancelButtonTitle?: string;
    /**
     * Title of the button that opens the screen where the user can allow
     * the usage of the camera by the app.
     */
    enableCameraButtonTitle?: string;
    /**
     * Text that will be displayed when the app
     * is not allowed to use the camera, prompting the user
     * to enable the usage of the camera.
     */
    enableCameraExplanationText?: string;
    /**
     * Height of the finder window in pixels.
     */
    finderHeight?: number;
    /**
     * Color of the finder window's outline.
     */
    finderLineColor?: string;
    /**
     * Thickness of the finder window's outline.
     */
    finderLineWidth?: number;
    /**
     * Text hint shown under the finder window.
     */
    finderTextHint?: string;
    /**
     * Color of the text hint under the finder window.
     */
    finderTextHintColor?: string;
    /**
     * Width of the finder window in pixels.
     */
    finderWidth?: number;
    flashButtonTitle?: string;
    /**
     * Controls whether the flash should be initially enabled.
     * The default value is FALSE.
     */
    flashEnabled?: boolean;
    /**
     * Orientation lock mode of the UI and the camera preview.
     * By default the orientation is not locked.
     */
    interfaceOrientation?: UIInterfaceOrientationMask;
    /**
     * Controls whether to play a beep sound after a successful detection.
     * Default value is TRUE.
     */
    successBeepEnabled?: boolean;
    /**
     * Background color of the top toolbar.
     */
    topBarBackgroundColor?: string;
    /**
     * Color of the titles of all buttons in the top toolbar.
     */
    topBarButtonsColor?: string;
    /**
     * Controls whether buttons should use all capitals style, as defined by the Android Material Design. Defaults to TRUE.
     * Android only.
     */
    useButtonsAllCaps?: boolean;
}

export type EngineMode =
    "NEXT_GEN" |
    "LEGACY"
    ;

export type BarcodeDocumentFormat =
    "AAMVA" |
    "BOARDING_PASS" |
    "DE_MEDICAL_PLAN" |
    "MEDICAL_CERTIFICATE" |
    "ID_CARD_PDF_417" |
    "SEPA" |
    "SWISS_QR" |
    "VCARD";

export interface BarcodeScannerConfiguration {
    /**
     * An optional array of barcode document formats that act as a detection filter.
     * By default all supported document formats will be detected.
     */
    acceptedDocumentFormats?: BarcodeDocumentFormat[];
    /**
     * Orientation lock mode of the UI and the camera preview.
     * By default the orientation is not locked.
     */
    interfaceOrientation?: UIInterfaceOrientationMask;
    /**
     * Background color of the detection overlay.
     */
    cameraOverlayColor?: string;
    /**
     * Whether the cancel button is hidden or not. (iOS only)
     */
    cancelButtonHidden?: boolean;
    /**
     * String being displayed on the cancel button.
     */
    cancelButtonTitle?: string;
    /**
     * Aspect ratio of finder frame (width \ height), which is used to build actual finder frame.
     * Default is 1 - it is a square frame, which is good for QR capturing.
     */
    finderAspectRatio?: FinderAspectRatio;
    /**
     * Foreground color of the detection overlay.
     */
    finderLineColor?: string;
    /**
     * Width of finder frame border. Default is 2.
     */
    finderLineWidth?: number;
    /**
     * String being displayed as description.
     */
    finderTextHint?: string;
    /**
     * Foreground color of the description label.
     */
    finderTextHintColor?: string;
    /**
     * Foreground color of the flash button when flash is off.
     */
    flashButtonInactiveColor?: string;
    /**
     * String being displayed on the flash button.
     */
    flashButtonTitle?: string;
    /**
     * Whether flash is toggled on or off.
     */
    flashEnabled?: boolean;
    /**
     * Whether scanner screen should make a sound on successful barcode or MRZ detection.
     */
    successBeepEnabled?: boolean;
    /**
     * Background color of the top bar.
     */
    topBarBackgroundColor?: string;
    /**
     * Foreground color of the cancel button and when flash button is on.
     */
    topBarButtonsColor?: string;
    /**
     * Accepted barcode formats
     */
    barcodeFormats?: BarcodeFormat[];
    /**
     * Specifies the way of barcode images generation or disables this generation at all.
     * Use, if you want to receive a full sized image with barcodes. Defaults to NONE.
     */
    barcodeImageGenerationType?: BarcodeImageGenerationType;
    /**
     * Controls whether buttons should use all capitals style, as defined by the Android Material Design. Defaults to TRUE.
     * Android only.
     */
    useButtonsAllCaps?: boolean;
    /**
     * Time in seconds until the screen is automatically cancelled. Set to 0 to disable automatic cancellation.
     * Defaults to 0 (disabled).
     */
    autoCancelTimeout?: number;
    /**
     * Optional minimum required text length of the detected barcode.
     * The default is 0 (setting is turned off).
     * NOTE: This feature works on ITF barcodes only.
     */
    minimumTextLength?: number,
    /**
     * Optional maximum required text length of the detected barcode.
     * The default is 0 (setting is turned off).
     * NOTE: This feature works on ITF barcodes only.
     */
    maximumTextLength?: number,
    /**
     * Optional minimum required quiet zone on the barcode.
     * Measured in modules (the size of minimal bar on the barcode).
     * The default is 10.
     * NOTE: This feature works on ITF barcodes only.
     */
    minimum1DBarcodesQuietZone?: number
    /**
     * The relative initial zoom level of the camera in the range [0,1], where 0 is zoomed out and 1 is zoomed in.
     * The default value is 0.
     */
    cameraZoomFactor?: number;
    /**
     * The engine mode of the barcode recognizer. Defaults to NEXT_GEN.
     * To use legacy recognizer, please specify LEGACY
     */
    engineMode?: EngineMode;
    /**
     * When set to `true`, the scanner assumes that the barcode can be a GS1 barcode.
     * Turn it off, if you don't want to see decoded FNC1 characters ("]C1" and ASCII char 29).
     * The default value is `true`.
     * NOTE: Currently works for CODE128 barcodes only!
     */
    gs1DecodingEnabled?: boolean;
    /**
     * The checksum algorithms for MSI Plessey barcodes.
     * The default value is [MSIPlesseyChecksumAlgorithm.Mod10].
     */
    msiPlesseyChecksumAlgorithm?: MSIPlesseyChecksumAlgorithm;
    /**
     * With this option enabled, the scanner removes checks digits for UPC, EAN and MSI Plessey codes.
     * Has no effect if both single and double digit MSI Plessey checksums are enabled.
     * The default is `false`
     */
    stripCheckDigits?: boolean;
    /**
     * If `true`, enabled the mode which slightly decreases the scanning quality and the energy consumption, and increases the scanning speed. If `false` - mode is disabled.
     * The default is `false`
     * Android only.
     */
    lowPowerMode?: boolean;
    /** 
     * Use a filter to determine which type of barcode can be detected; see `BarcodeFilter`
     */
    barcodeFilter?: BarcodeFilter
    /* 
     * The expected density of QR codes. A higher density finds more QR codes in an image but the performance is slightly reduced.
     */
    codeDensity?: CodeDensity;
}

export interface BatchBarcodeScannerConfiguration {
    /**
     * An optional array of barcode document formats that act as a detection filter.
     * By default all supported document formats will be detected.
     */
    acceptedDocumentFormats?: BarcodeDocumentFormat[];
    /**
     * Orientation lock mode of the UI and the camera preview.
     * By default the orientation is not locked.
     */
    interfaceOrientation?: UIInterfaceOrientationMask;
    /**
     * String used for displaying amount of scanned barcodes. Use %d for number formatting symbol.
     */
    barcodesCountText?: string;
    /**
     * Text color of the barcodes count label.
     */
    barcodesCountTextColor?: string;
    /**
     * Background color of the detection overlay.
     */
    cameraOverlayColor?: string;
    /**
     * Whether the cancel button is hidden or not. (iOS only)
     */
    cancelButtonHidden?: boolean;
    /**
     * String being displayed on the cancel button.
     */
    cancelButtonTitle?: string;
    /**
     * String being displayed on the clear button.
     */
    clearButtonTitle?: string;
    /**
     * String being displayed on the delete button.
     */
    deleteButtonTitle?: string;
    /**
     * Foreground color of the top bar buttons on the details screen.
     */
    detailsActionColor?: string;
    /**
     * Background color of the details screen.
     */
    detailsBackgroundColor?: string;
    /**
     * Text color in the details barcodes list. Also affects image background, separator and progress spinner.
     */
    detailsPrimaryColor?: string;
    /**
     * String used to show process of fetching mapped data for barcodes.
     */
    fetchingStateText?: string;
    /**
     * Aspect ratio of finder frame (width \ height), which is used to build actual finder frame.
     * Default is 1 - it is a square frame, which is good for QR capturing.
     */
    finderAspectRatio?: FinderAspectRatio;
    /**
     * Foreground color of the detection overlay.
     */
    finderLineColor?: string;
    /**
     * Width of finder frame border. Default is 2.
     */
    finderLineWidth?: number;
    /**
     * String being displayed as description.
     */
    finderTextHint?: string;
    /**
     * Foreground color of the description label.
     */
    finderTextHintColor?: string;
    /**
     * Whether flash is toggled on or off.
     */
    flashEnabled?: boolean;
    /**
     * String to show that no barcodes were scanned yet.
     */
    noBarcodesTitle?: string;
    /**
     * Enables or disables the barcode detection.
     */
    recognitionEnabled?: boolean;
    /**
     * String being displayed on the submit button.
     */
    submitButtonTitle?: string;
    /**
     * Whether scanner screen should make a sound on successful barcode or MRZ detection.
     */
    successBeepEnabled?: boolean;
    /**
     * Background color of the top bar.
     */
    topBarBackgroundColor?: string;
    /**
     * Foreground color of the top bar buttons on the scanning screen.
     */
    topBarButtonsColor?: string;
    /**
     * Foreground color of the flash button when flash is off.
     */
    topBarButtonsInactiveColor?: string;
    /**
     * Accepted barcode formats
     */
    barcodeFormats?: BarcodeFormat[];
    /**
     * Controls whether buttons should use all capitals style, as defined by the Android Material Design. Defaults to TRUE.
     * Android only.
     */
    useButtonsAllCaps?: boolean;
    /**
    * Optional minimum required text length of the detected barcode.
    * The default is 0 (setting is turned off).
    * NOTE: This feature works on ITF barcodes only.
    */
    minimumTextLength?: number,
    /**
     * Optional maximum required text length of the detected barcode.
     * The default is 0 (setting is turned off).
     * NOTE: This feature works on ITF barcodes only.
     */
    maximumTextLength?: number,
    /**
     * Optional minimum required quiet zone on the barcode.
     * Measured in modules (the size of minimal bar on the barcode).
     * The default is 10.
     * NOTE: This feature works on ITF barcodes only.
     */
    minimum1DBarcodesQuietZone?: number
    /**
     * The engine mode of the barcode recognizer. Defaults to NEXT_GEN.
     * To use legacy recognizer, please specify LEGACY
     */
    engineMode?: EngineMode;
    /**
     * When set to `true`, the scanner assumes that the barcode can be a GS1 barcode.
     * Turn it off, if you don't want to see decoded FNC1 characters ("]C1" and ASCII char 29).
     * The default value is `true`.
     * NOTE: Currently works for CODE128 barcodes only!
     */
    gs1DecodingEnabled?: boolean;
    /**
     * The checksum algorithms for MSI Plessey barcodes.
     * The default value is [MSIPlesseyChecksumAlgorithm.Mod10].
     */
    msiPlesseyChecksumAlgorithm?: MSIPlesseyChecksumAlgorithm;
    /**
     * With this option enabled, the scanner removes checks digits for UPC, EAN and MSI Plessey codes.
     * Has no effect if both single and double digit MSI Plessey checksums are enabled.
     * The default is `false`
     */
    stripCheckDigits?: boolean;
    /**
     * If `true`, enabled the mode which slightly decreases the scanning quality and the energy consumption, and increases the scanning speed. If `false` - mode is disabled.
     * The default is `false`
     * Android only.
     */
    lowPowerMode?: boolean;
    /** 
    * Use a filter to determine which type of barcode can be detected; see `BarcodeFilter`
    */
    barcodeFilter?: BarcodeFilter
    /* 
     * The expected density of QR codes. A higher density finds more QR codes in an image but the performance is slightly reduced.
     */
    codeDensity?: CodeDensity;
}

export interface HealthInsuranceCardScannerConfiguration {
    /**
     * Orientation lock mode of the UI and the camera preview.
     * By default the orientation is not locked.
     */
    interfaceOrientation?: UIInterfaceOrientationMask;
    /**
     * Background color of the detection overlay.
     */
    cameraOverlayColor?: string;
    /**
     * Whether the cancel button is hidden or not. (iOS only)
     */
    cancelButtonHidden?: boolean;
    /**
     * String being displayed on the cancel button.
     */
    cancelButtonTitle?: string;
    /**
     * The receivers delegate.
     */
    delegate?: any;
    /**
     * String being displayed when health insurance card was not found.
     */
    detectionStatusFailedDetectionText?: string;
    /**
     * String being displayed when health insurance card was found but not recognized.
     */
    detectionStatusFailedValidationText?: string;
    /**
     * String being displayed when health insurance card was found and recognized.
     */
    detectionStatusSuccessText?: string;
    /**
     * Foreground color of the detection overlay.
     */
    finderLineColor?: string;
    /**
     * Width of finder frame border. Default is 2.
     */
    finderLineWidth?: number;
    /**
     * String being displayed as description.
     */
    finderTextHint?: string;
    /**
     * Foreground color of the description label.
     */
    finderTextHintColor?: string;
    /**
     * String being displayed on the flash button.
     */
    flashButtonTitle?: string;
    /**
     * Whether flash is toggled on or off.
     */
    flashEnabled?: boolean;
    /**
     * Enables or disables the machine readable zones detection.
     */
    recognitionEnabled?: boolean;
    /**
     * Background color of the top bar.
     */
    topBarBackgroundColor?: string;
    /**
     * Foreground color of the cancel button and the flash button (iOS only) when the flash is active.
     */
    topBarButtonsColor?: string;
    /**
     * Foreground color of the flash button when flash is off (iOS only)
     */
    flashButtonInactiveColor?: string;
    /**
     * The type of health insurance card validation.
     */
    validationType?: HealthInsuranceCardValidationType;
    /**
     * Controls whether buttons should use all capitals style, as defined by the Android Material Design. Defaults to TRUE.
     * Android only.
     */
    useButtonsAllCaps?: boolean;
}

export interface LicensePlateScannerConfiguration {
    /**
     * Background color of the top bar.
     */
    topBarBackgroundColor?: string;
    /**
     * Color of the top bar buttons.
     */
    topBarButtonsColor?: string;
    /**
     * String being displayed on the cancel button.
     */
    cancelButtonTitle?: string;
    /**
     * Color of the finder window's outline.
     */
    finderLineColor?: string;
    /**
     * Thickness of the finder window's outline.
     */
    finderLineWidth?: number;
    /**
     * Color of the text hint under the finder window.
     */
    finderTextHintColor?: string;
    /**
     * Should the flashlight be enabled on start?
     */
    flashEnabled?: boolean;
    /**
     * Controls whether buttons should use all capitals style, as defined by the Android Material Design. Defaults to TRUE.
     * Android only.
     */
    useButtonsAllCaps?: boolean;
    /**
     * Title of the button that opens the screen where the user can allow
     * the usage of the camera by the app.
     */
    enableCameraButtonTitle?: string;
    /**
     * Text that will be displayed when the app
     * is not allowed to use the camera, prompting the user
     * to enable the usage of the camera.
     */
    enableCameraExplanationText?: string;
    /**
     * Orientation lock mode of the UI and the camera preview.
     * By default the orientation is not locked.
     */
    interfaceOrientation?: UIInterfaceOrientationMask;
    /**
     * Detector mode, classic (OCR based) or ML (machine learning based) approach.
     */
    detectorMode?: LicensePlateDetectorMode;
    /**
     * User guidance hint text.
     */
    guidanceText?: string;
    /**
     * Maximum number of accumulated frames to inspect before actual result is returned.
     */
    maximumNumberOfAccumulatedFrames?: number;
    /**
     * Minimum number of accumulated frames that must have equal result.
     */
    minNumberOfRequiredFramesWithEqualRecognitionResult?: number;
    /**
     * Color of the titles of buttons in the top toolbar when inactive.
     */
    topBarButtonsInactiveColor?: string;
    /**
     * Background color outside of the finder window.
     */
    cameraOverlayColor?: string;
    /**
     * The title of the confirmation dialog.
     */
    confirmationDialogTitle?: string;
    /**
     * The message text of the confirmation dialog.
     */
    confirmationDialogMessage?: string;
    /**
     * The title of the confirmation dialog retry button.
     */
    confirmationDialogRetryButtonTitle?: string;
    /**
     * The title of the confirmation dialog confirm button.
     */
    confirmationDialogConfirmButtonTitle?: string;
    /**
     * The accent color of buttons on a confirmation dialog.
     */
    confirmationDialogAccentColor?: string;
    /**
     * Allows to set if the confirm button should be filled. Defaults to TRUE.
     */
    confirmationDialogConfirmButtonFilled?: boolean;
    /**
     * Allows to set a text color of the filled button. See `confirmationDialogConfirmButtonFilled`.
     */
    confirmationDialogConfirmButtonFilledTextColor?: string;
}

export interface DataScannerConfiguration {
    /**
     * Background color of the top bar.
     */
    topBarBackgroundColor?: string;
    /**
     * Color of the top bar buttons.
     */
    topBarButtonsColor?: string;
    /**
     * String being displayed on the cancel button.
     */
    cancelButtonTitle?: string;
    /**
     * Color of the finder window's outline.
     */
    finderLineColor?: string;
    /**
     * Thickness of the finder window's outline.
     */
    finderLineWidth?: number;
    /**
     * Color of the text hint under the finder window.
     */
    finderTextHintColor?: string;
    /**
     * Should the flashlight be enabled on start?
     */
    flashEnabled?: boolean;
    /**
     * Controls whether buttons should use all capitals style, as defined by the Android Material Design. Defaults to TRUE.
     * Android only.
     */
    useButtonsAllCaps?: boolean;
    /**
     * Title of the button that opens the screen where the user can allow
     * the usage of the camera by the app.
     */
    enableCameraButtonTitle?: string;
    /**
     * Text that will be displayed when the app
     * is not allowed to use the camera, prompting the user
     * to enable the usage of the camera.
     */
    enableCameraExplanationText?: string;
    /**
     * Orientation lock mode of the UI and the camera preview.
     * By default the orientation is not locked.
     */
    interfaceOrientation?: UIInterfaceOrientationMask;
}

export interface TextDataScannerStep {
    /**
     * User guidance hint text.
     */
    guidanceText: string;
    /**
     * Validation pattern to automatically validate recognized text.
     * '?' = any character,
     * '#' - any digit,
     * all other characters represent themselves.
     * An empty string or nil value will disable the validation pattern.
     */
    pattern?: string;
    /**
     * If set to TRUE pattern validation also validates successfully if only a part of the whole recognized text matches
     * the the validation pattern.
     * If set to FALSE, the whole text must match the validation pattern.
     * Applies to pattern validation only. Defaults to FALSE.
     */
    shouldMatchSubstring?: boolean;
    /**
     * The cameras zoom level preferred for this step. The actual zoom might be different from the preferred one
     * to avoid clipping of finder area and maintain its aspect ratio and height;
     */
    preferredZoom?: number;
    /**
     * The aspect ratio of the view finder area.
     */
    aspectRatio?: FinderAspectRatio;
    /**
     * The preferred height of the finder for zoom scale 1.0 (unzoomed).
     * The actual finder height might change to maintain aspect ratio and to not clip the screen.
     * Defaults to 40 points.
     */
    unzoomedFinderHeight?: number;
    /**
     * A string (list) of accepted characters during text recognition. If empty or nil, all characters are accepted.
     * Defaults to nil.
     */
    allowedSymbols?: string;
    /**
     * Recognition strategy for the text.
     */
    textFilterStrategy?: TextFilterStrategy;
    /**
     * Threshold used to pause the detection after significant movement occurred.
     * -1 is default value
     * Default = 0 for textFilterStrategy='DOCUMENT' and 1000 for textFilterStrategy='LCD_DOT_MATRIX_DISPLAY'
     */
    significantShakeDelay?: number;
}

interface InternalBarcodeDetectionCommonParameters {
    /**
     * Accepted barcode formats.
     */
    barcodeFormats?: BarcodeFormat[];
    /**
     * An optional array of barcode document formats that acts as a detection filter.
     * By default all supported document formats will be detected.
     */
    acceptedDocumentFormats?: BarcodeDocumentFormat[];
    /** 
     * Use a filter to determine which type of barcode can be detected; see `BarcodeFilter`
     */
    barcodeFilter?: BarcodeFilter;
    /**
     * If `true`, enables the mode which slightly decreases the scanning quality and the energy consumption, thus increasing the scanning speed.
     * The default is `false`.
     * Android only.
     */
    lowPowerMode?: boolean;
    /**
     * Optional minimum required text length of the detected barcode.
     * The default is 0 (setting is turned off).
     * NOTE: This feature works on ITF and MSI Plessey barcodes only.
     */
    minimumTextLength?: number;
    /**
     * Optional maximum required text length of the detected barcode.
     * The default is 0 (setting is turned off).
     * NOTE: This feature works on ITF and MSI Plessey barcodes only.
     */
    maximumTextLength?: number;
    /**
     * Optional minimum required quiet zone on the barcode.
     * Measured in modules (the size of narrowest bar in the barcode).
     * The default is 10.
     * NOTE: This feature works on ITF and MSI Plessey barcodes only.
     */
    minimum1DBarcodesQuietZone?: number;
    /**
     * With this option enabled, the scanner removes check digits for UPC, EAN and MSI Plessey codes.
     * Has no effect if both single and double digit MSI Plessey checksums are enabled.
     * The default is `false`.
     */
    stripCheckDigits?: boolean;
    /**
     * When set to `true`, the scanner assumes that the barcode can be a GS1 barcode.
     * Turn it off if you don't want to see decoded FNC1 characters ("]C1" and ASCII char 29).
     * The default value is `true`.
     * NOTE: Currently works for CODE128 barcodes only!
     */
    gs1DecodingEnabled?: boolean;
    /**
    * The checksum algorithm for MSI Plessey barcodes.
    * The default value is [MSIPlesseyChecksumAlgorithm.Mod10].
    */
    msiPlesseyChecksumAlgorithm?: MSIPlesseyChecksumAlgorithm;
    /* 
     * The expected density of QR codes. A higher density finds more QR codes in an image but the performance is slightly reduced.
     */
    codeDensity?: CodeDensity;
}

export interface DetectBarcodesOnImageArgs extends InternalBarcodeDetectionCommonParameters {
    /** 
    * The input image file URI.
    */
    imageFileUri: string;
}

export interface DetectBarcodesOnImagesArgs extends InternalBarcodeDetectionCommonParameters {
    /** 
    * The list of input image files URIs.
    */
    imageFilesUris: string[];
}

export type LicensePlateDetectorMode = "CLASSIC" | "ML_BASED";

export type TextFilterStrategy = "DOCUMENT" | "LC_DOT_MATRIX_DISPLAY";

export type HealthInsuranceCardValidationType =
    "NONE"
    | "AUTO_ANY"
    | "AUTO_SUPPORTED"
    | "GERMAN"
    | "AUSTRIAN"
    ;

export type UIInterfaceOrientationMask =
    | "ALL"
    | "PORTRAIT"
    | "LANDSCAPE"
    ;

export type BarcodeFormat =
    "AZTEC" |
    "CODABAR" |
    "CODE_39" |
    "CODE_93" |
    "CODE_128" |
    "DATA_MATRIX" |
    "EAN_8" |
    "EAN_13" |
    "ITF" |
    "PDF_417" |
    "QR_CODE" |
    "RSS_14" |
    "RSS_EXPANDED" |
    "UPC_A" |
    "UPC_E" |
    "MSI_PLESSEY" |
    "UNKNOWN";

export type CodeDensity = 'LOW' | 'HIGH';

export type BarcodeImageGenerationType = "NONE" | "VIDEO_FRAME" | "CAPTURED_IMAGE";

export type CameraPreviewMode = "FILL_IN" | "FIT_IN";

export type CameraImageFormat = "JPG" | "PNG";

export type FileEncryptionMode = "AES128" | "AES256";

export type MSIPlesseyChecksumAlgorithm =
    "None" |
    "Mod10" |
    "Mod11IBM" |
    "Mod11NCR" |
    "Mod1010" |
    "Mod1110IBM" |
    "Mod1110NCR"
    ;

export type DetectionStatus =
    "OK"
    | "OK_BUT_TOO_SMALL"
    | "OK_BUT_BAD_ANGLES"
    | "OK_BUT_BAD_ASPECT_RATIO"
    | "OK_BARCODE"
    | "OK_OFF_CENTER"
    | "ERROR_NOTHING_DETECTED"
    | "ERROR_TOO_DARK"
    | "ERROR_TOO_NOISY"
    ;

export type Status = "OK" | "CANCELED";

export type HealthInsuranceCardDetectionStatus = "SUCCESS" | "FAILED_DETECTION" | "FAILED_VALIDATION";

export type ImageFilter =
    "NONE"
    | "COLOR_ENHANCED"
    | "GRAYSCALE"
    | "BINARIZED"
    | "COLOR_DOCUMENT"
    | "PURE_BINARIZED"
    | "BACKGROUND_CLEAN"
    | "BLACK_AND_WHITE"
    | "OTSU_BINARIZATION"
    | "DEEP_BINARIZATION"
    | "LOW_LIGHT_BINARIZATION"
    | "LOW_LIGHT_BINARIZATION_2"
    | "EDGE_HIGHLIGHT"
    | "SENSITIVE_BINARIZATION"
    ;

export type OCROutputFormat =
    "PLAIN_TEXT"
    | "RESULT_JSON"
    | "PDF_FILE"
    | "FULL_OCR_RESULT"
    ;

export type PDFPageSize =
    "FROM_IMAGE"
    | "A4"
    | "FIXED_A4"
    | "US_LETTER"
    | "FIXED_US_LETTER"
    | "AUTO_LOCALE"
    | "AUTO"
    ;

export type TIFFCompression =
    "NONE"
    | "CCITTRLE"
    | "CCITTFAX3"
    | "CCITT_T4"
    | "CCITTFAX4"
    | "CCITT_T6"
    | "CCITTRLEW"
    | "LZW"
    | "PACKBITS"
    | "DEFLATE"
    | "ADOBE_DEFLATE"
    ;

export type RootDocumentType =
    "DeIdBack"
    | "DeIdFront"
    | "DePassport"
    | "DeDriverLicenseFront"
    | "DeDriverLicenseBack"
    ;

export type BarcodeFilter =
    "WithExtension"
    | "WithEAN2Extension"
    | "WithEAN5Extension";

export type CameraModule = 'FRONT' | 'BACK';

export interface DocumentDetectionResult {
    detectionResult: DetectionStatus;
    polygon?: Point[];
    documentImageFileUri?: string;
}

export interface Point {
    x: number;
    y: number;
}

export interface Size {
    width: number;
    height: number;
}

export interface Page {
    pageId: string;
    polygon: Point[];
    detectionResult: DetectionStatus;
    filter: ImageFilter;
    isCapturedAutomatically: boolean;
    documentImageSizeLimit?: Size;

    originalImageFileUri: string;
    documentImageFileUri?: string;
    originalPreviewImageFileUri: string;
    documentPreviewImageFileUri?: string;
}

export interface DocumentScannerResult {
    status: Status;
    pages: Page[];
}

export interface CroppingResult {
    status: Status;
    page?: Page;
}

export interface MrzResult {
    status: Status;
    mrzResult?: {
        fields: {
            name: string;
            value: string;
            confidence: number;
        }[];
        checkDigitsCount: number;
        validCheckDigitsCount: number;
    }
}

export interface HealthInsuranceCardScannerResult {
    status: Status;
    ehicResult?: {
        fields: {
            type: string;
            value: string;
            confidence: number;
        }[];
    }
}

export interface LicensePlateScannerResult {
    status: Status;
    licensePlateResult?: {
        rawText: string;
        countryCode: string;
        licensePlate: string;
        confidence: number;
    }
}

export interface DataScannerResult {
    status: Status;
    dataResult?: {
        textValue: string;
        confidence: number;
    }
}

export interface FinderAspectRatio {
    width: number;
    height: number;
}

export interface LicenseInfo {
    isLicenseValid: boolean;
    licenseStatus: LicenseStatus;
    licenseExpirationDate?: number;
}

export interface LicenseFailure {
    licenseStatus: LicenseStatus;
    licenseFeature: LicenseFeature;
    licenseErrorMessage: string;
}

export type LicenseStatus = "Okay" | "Trial" | "Expired" |
    "WrongOS" | "Corrupted" | "AppIDMismatch" | "NotSet" | "Unknown";

export type LicenseFeature =
    "Check" | "OCR" | "QRCode" | "NoFeature" |
    "CloudUpload" | "PDFCreation" | "W2Detection" |
    "EdgeDetection" | "CreditCardRecognition" |
    "DataIntelligence" | "MRZRecognition" |
    "MedicalCertRecognition" | "EdgeDetectionUI" |
    "EHICRecognition" | "ImageProcessing" |
    "InvoiceDetection" | "MultipleObjectsDetection" |
    "PayformDetection" | "TextOrientationDetection" | "Unknown";

export type DocumentDetectorMode = "EDGE_BASED" | "ML_BASED";

export interface BarcodeResultField {
    /**
     * The barcode format.
     */
    type: BarcodeFormat;

    /**
     * The raw text encoded in the barcode.
     */
    text: string;

    /**
     * The raw text with extension encoded in the barcode
     */
    textWithExtension: string

    /**
    * The array of raw bytes contained in the barcode.
    */
    rawBytes: number[];
}

export interface BarcodeResult {
    status: Status;
    canceledDueToTimeout?: boolean;
    barcodes?: BarcodeResultField[];
    /**
     * Optional file URI of the captured camera image. Available only when
     * `configs.barcodeImageGenerationType` is not `"NONE"`.
     */
    imageFileUri?: string;
}

export interface GenericResult {
    status: Status;
    message?: string;
}

export interface DetectBarcodesOnImagesResult {
    results?: [
        {
            imageFileUri: string,
            barcodeResults: BarcodeResultField[],
            error?: string
        }
    ]
}

///// Promisified Scanbot API

export interface ScanbotSDKConfiguration {
    licenseKey: string;
    loggingEnabled?: boolean;
    enableNativeLogging?: boolean;
    storageImageQuality?: number;
    storageImageFormat?: CameraImageFormat;
    storageBaseDirectory?: string;
    documentDetectorMode?: DocumentDetectorMode
    fileEncryptionPassword?: string;
    fileEncryptionMode?: FileEncryptionMode;
    useCameraX?: boolean;
    allowXnnpackAcceleration?: boolean;
    allowGpuAcceleration?: boolean;
}

export interface ScanbotSDKUI {
    startDocumentScanner(args?: { uiConfigs?: DocumentScannerConfiguration }): Promise<DocumentScannerResult>;
    startCroppingScreen(args: { page: Page; uiConfigs?: CroppingScreenConfiguration }): Promise<CroppingResult>;
    startMrzScanner(args?: { uiConfigs?: MrzScannerConfiguration }): Promise<MrzResult>;
    startBarcodeScanner(args?: { uiConfigs?: BarcodeScannerConfiguration }): Promise<BarcodeResult>;
    startBatchBarcodeScanner(args?: { uiConfigs?: BatchBarcodeScannerConfiguration }): Promise<BarcodeResult>;
    startEHICScanner(args?: { uiConfigs?: HealthInsuranceCardScannerConfiguration }): Promise<HealthInsuranceCardScannerResult>;
    startLicensePlateScanner(args?: { uiConfigs?: LicensePlateScannerConfiguration }): Promise<LicensePlateScannerResult>;
    startDataScanner(args?: { uiConfigs?: DataScannerConfiguration, scannerStep: TextDataScannerStep }): Promise<DataScannerResult>;
    startGenericDocumentRecognizer(args?: { uiConfigs?: GenericDocumentRecognizerConfiguration }): Promise<GenericDocumentRecognizerResult>;
    startCheckRecognizer(args?: { uiConfigs?: CheckRecognizerConfiguration }): Promise<CheckRecognizerResult>;
}

export interface ScanbotSDK {
    UI: ScanbotSDKUI;

    initializeSdk(config: ScanbotSDKConfiguration): Promise<GenericResult>;
    getLicenseInfo(): Promise<GenericResult & { info: LicenseInfo }>;

    detectDocument(args: {
        imageFileUri: string,
        quality?: number
    }): Promise<GenericResult & DocumentDetectionResult>;
    detectBarcodesOnImage(
        args: DetectBarcodesOnImageArgs
    ): Promise<GenericResult & BarcodeResult>;
    detectBarcodesOnImages(
        args: DetectBarcodesOnImagesArgs
    ): Promise<GenericResult & DetectBarcodesOnImagesResult>
    applyImageFilter(args: {
        imageFileUri: string,
        imageFilter: ImageFilter,
        quality?: number
    }): Promise<GenericResult & { imageFileUri: string }>;
    rotateImage(args: {
        imageFileUri: string,
        degrees: number,
        quality?: number
    }): Promise<GenericResult & { imageFileUri: string }>;

    getOcrConfigs(): Promise<GenericResult & { languageDataPath: string; installedLanguages: string[]; }>;
    performOcr(
        args: {
            images: string[]; languages: string[]; outputFormat?: OCROutputFormat;
        }): Promise<GenericResult & { plainText?: string; pdfFileUri?: string; jsonData?: any; }>;

    createPdf(args: { images: string[], pageSize: PDFPageSize }): Promise<GenericResult & { pdfFileUri: string; }>;

    writeTiff(args: {
        images: string[];
        oneBitEncoded?: boolean;
        dpi?: number;
        compression?: TIFFCompression;
    }): Promise<GenericResult & { tiffFileUri: string; }>;

    createPage(args: { originalImageFileUri: string }): Promise<GenericResult & { page: Page }>;
    setDocumentImage(args: { page: Page; documentImageFileUri: string }): Promise<GenericResult & { page: Page }>;
    detectDocumentOnPage(args: { page: Page }): Promise<GenericResult & { page: Page }>;
    applyImageFilterOnPage(args: { page: Page, imageFilter: ImageFilter }): Promise<GenericResult & { page: Page }>;
    rotatePage(args: { page: Page, times: number }): Promise<GenericResult & { page: Page }>;
    getFilteredDocumentPreviewUri(
        args: { page: Page, imageFilter: ImageFilter }): Promise<GenericResult & { imageFileUri: string }>;
    removePage(args: { page: Page }): Promise<GenericResult>;

    estimateBlur(args: { imageFileUri: string }): Promise<GenericResult & { blur: number }>;

    cleanup(): Promise<GenericResult>;

    requestCameraPermission(): Promise<GenericResult>;

    refreshImageUris(args: { pages: Page[] }): Promise<GenericResult & { pages: Page[] }>;

    getImageData(args: { imageFileUri: string }): Promise<GenericResult & { base64ImageData: string }>;
}

///// Base Cordova API

type SuccessCallback<TResult> = (result: TResult) => void;
type ErrorCallback = (error: {
    status: "ERROR";
    message: string;
}) => void;

export interface ScanbotSDKUICordova {
    startDocumentScanner(
        success: SuccessCallback<DocumentScannerResult>,
        error: ErrorCallback,
        args?: { uiConfigs?: DocumentScannerConfiguration });
    startCroppingScreen(
        success: SuccessCallback<CroppingResult>,
        error: ErrorCallback,
        args: { page: Page; uiConfigs?: CroppingScreenConfiguration });
    startMrzScanner(
        success: SuccessCallback<MrzResult>,
        error: ErrorCallback,
        args?: { uiConfigs?: MrzScannerConfiguration });
    startBarcodeScanner(
        success: SuccessCallback<BarcodeResult>,
        error: ErrorCallback,
        args?: { uiConfigs?: BarcodeScannerConfiguration });
    startBatchBarcodeScanner(
        success: SuccessCallback<BarcodeResult>,
        error: ErrorCallback,
        args?: { uiConfigs?: BatchBarcodeScannerConfiguration });
    startEHICScanner(
        success: SuccessCallback<HealthInsuranceCardScannerResult>,
        error: ErrorCallback,
        args?: { uiConfigs?: HealthInsuranceCardScannerConfiguration });
    startLicensePlateScanner(
        success: SuccessCallback<LicensePlateScannerResult>,
        error: ErrorCallback,
        args?: { uiConfigs?: LicensePlateScannerConfiguration });
    startDataScanner(
        success: SuccessCallback<DataScannerResult>,
        error: ErrorCallback,
        args?: { uiConfigs?: DataScannerConfiguration, scannerStep: TextDataScannerStep });
    startGenericDocumentRecognizer(
        success: SuccessCallback<GenericDocumentRecognizerResult>,
        error: ErrorCallback,
        args?: { uiConfigs?: GenericDocumentRecognizerConfiguration });
}

export interface ScanbotSDKCordova {
    /**
     * Returns a promisified version of the Scanbot SDK API.
     * Available only if there is also an available Promise global function.
     */
    promisify?(): ScanbotSDK;

    UI: ScanbotSDKUICordova;

    initializeSdk(
        success: SuccessCallback<GenericResult>,
        error: ErrorCallback,
        config: ScanbotSDKConfiguration): void;
    getLicenseInfo(
        success: SuccessCallback<GenericResult & { info: LicenseInfo }>,
        error: ErrorCallback): void;
    setLicenseFailureHandler(callback: SuccessCallback<LicenseFailure>): void;

    detectBarcodesOnImage(
        success: SuccessCallback<GenericResult & BarcodeResult>,
        error: ErrorCallback, args: {
            imageFileUri: string,
            barcodeFormats?: BarcodeFormat[],
            acceptedDocumentFormats?: BarcodeDocumentFormat[],
            minimumTextLength?: number, // NOTE: This feature works on ITF barcodes only.
            maximumTextLength?: number, // NOTE: This feature works on ITF barcodes only.
            minimum1DBarcodesQuietZone?: number //NOTE: This feature works on ITF barcodes only. 
            msiPlesseyChecksumAlgorithm?: MSIPlesseyChecksumAlgorithm;
        }): void;

    detectBarcodesOnImages(
        success: SuccessCallback<GenericResult & DocumentDetectionResult>,
        error: ErrorCallback, args: {
            imageFilesUris: string[],
            barcodeFormats?: BarcodeFormat[],
            acceptedDocumentFormats?: BarcodeDocumentFormat[],
            minimumTextLength?: number, // NOTE: This feature works on ITF barcodes only.
            maximumTextLength?: number, // NOTE: This feature works on ITF barcodes only.
            minimum1DBarcodesQuietZone?: number //NOTE: This feature works on ITF barcodes only.
            msiPlesseyChecksumAlgorithm?: MSIPlesseyChecksumAlgorithm;
        }
    ): void
    detectDocument(
        success: SuccessCallback<GenericResult & DocumentDetectionResult>,
        error: ErrorCallback, args: { imageFileUri: string, quality?: number }): void;
    applyImageFilter(
        success: SuccessCallback<GenericResult & { imageFileUri: string }>,
        error: ErrorCallback, args: {
            imageFileUri: string, imageFilter: ImageFilter, quality?: number
        }): void;
    rotateImage(
        success: SuccessCallback<GenericResult & { imageFileUri: string }>,
        error: ErrorCallback, args: {
            imageFileUri: string, degrees: number, quality?: number
        }): void;
    getOcrConfigs(
        success: SuccessCallback<GenericResult & { languageDataPath: string; installedLanguages: string[]; }>,
        error: ErrorCallback): void;
    performOcr(
        success: SuccessCallback<GenericResult & { plainText?: string; pdfFileUri?: string; jsonData?: any; }>,
        error: ErrorCallback, args: {
            images: string[]; languages: string[]; outputFormat?: OCROutputFormat;
        }): void;

    createPdf(
        success: SuccessCallback<GenericResult & { pdfFileUri: string }>,
        error: ErrorCallback,
        args: { images: string[], pageSize: PDFPageSize }): void;

    writeTiff(success: SuccessCallback<GenericResult & { tiffFileUri: string }>, error: ErrorCallback, args: {
        images: string[];
        oneBitEncoded?: boolean;
        dpi?: number;
        compression?: TIFFCompression;
    }): void;

    createPage(
        success: SuccessCallback<GenericResult & { page: Page }>,
        error: ErrorCallback,
        args: { originalImageFileUri: string }): void;
    setDocumentImage(
        success: SuccessCallback<GenericResult & { page: Page }>,
        error: ErrorCallback,
        args: { page: Page, imageUri: string }): void;
    detectDocumentOnPage(
        success: SuccessCallback<GenericResult & { page: Page }>,
        error: ErrorCallback,
        args: { page: Page }): void;
    applyImageFilterOnPage(
        success: SuccessCallback<GenericResult & { page: Page }>,
        error: ErrorCallback,
        args: { page: Page, imageFilter: ImageFilter }): void;
    rotatePage(
        success: SuccessCallback<GenericResult & { page: Page }>,
        error: ErrorCallback,
        args: { page: Page, times: number }): void;
    getFilteredDocumentPreviewUri(
        success: SuccessCallback<GenericResult & { imageFileUri: string }>,
        error: ErrorCallback,
        args: { page: Page, imageFilter: ImageFilter }): void;
    removePage(
        success: SuccessCallback<GenericResult>,
        error: ErrorCallback, page: Page): void;

    estimateBlur(
        success: SuccessCallback<GenericResult & { blur: number }>,
        error: ErrorCallback,
        args: { imageFileUri: string }): void;

    cleanup(success: SuccessCallback<GenericResult>, error: ErrorCallback): void;

    refreshImageUris(
        success: SuccessCallback<GenericResult & { pages: Page[] }>,
        error: ErrorCallback,
        args: { pages: Page[] }): void;

    getImageData(
        success: SuccessCallback<GenericResult & { base64ImageData: string }>,
        error: ErrorCallback,
        args: { imageFileUri: string }): void;
}

declare let ScanbotSDK: ScanbotSDKCordova;

export default ScanbotSDK;
