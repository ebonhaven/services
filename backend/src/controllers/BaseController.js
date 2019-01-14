const BaseController = () => {
    const get = (req, res) => {
        res.json({"hello": "world", "id": req.params.id});
    };

    return {
        get
    }
};

export default BaseController;