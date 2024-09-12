import { CoreFeatureIdEnum } from "../enums/core_feature_id_enum";
import { CoreFeatureEnum } from "../enums/core_feature_enum";

export class CoreFeatureModel {
    id: CoreFeatureIdEnum;
    title: string;
    description: string;
    items: { key: CoreFeatureEnum; value: string; }[];

    constructor(id: CoreFeatureIdEnum, title: string, description: string, items: { key: CoreFeatureEnum; value: string; }[]) {
        this.id = id,
            this.title = title,
            this.description = description,
            this.items = items
    }
};